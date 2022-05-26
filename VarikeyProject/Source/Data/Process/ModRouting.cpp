/*
  ==============================================================================

    ModRouting.cpp
    Created: 20 May 2022 8:43:53pm
    Author:  juanp

  ==============================================================================
*/

#include "ModRouting.h"

void ModRouting::setInModList(int modIndex, float paramMin, float paramMax, bool modAroundValue = false)
{
    paramMins[modIndex] = paramMin;
    paramMaxs[modIndex] = paramMax;
    modAroundVal[modIndex] = modAroundValue;
}

void ModRouting::updateModRoutes(int lfo1, int lfo2, int lfo3, int lfo4, int adsr)
{
    lfo1Route = lfo1;
    setCurrentRoutes(lfo1Route, 1);
    lfo2Route = lfo2;
    setCurrentRoutes(lfo2Route, 2);
    lfo3Route = lfo3;
    setCurrentRoutes(lfo3Route, 3);
    lfo4Route = lfo4;
    setCurrentRoutes(lfo4Route, 4);
    modAdsrRoute = adsr;
    setCurrentRoutes(modAdsrRoute, 5);

    //for (int i = 0; i < paramNumber; i++)
    //{
    //    if (!isUsedRoute(i)) modState[i]
    //}

}

void ModRouting::updateModValues(float lfo1, float lfo2, float lfo3, float lfo4)
{
    lfo1Sample = lfo1;
    lfo2Sample = lfo2;
    lfo3Sample = lfo3;
    lfo4Sample = lfo4;
}

void ModRouting::updateModDepth(float lfo1, float lfo2, float lfo3, float lfo4)
{
    lfo1Depth = lfo1;
    lfo2Depth = lfo2;
    lfo3Depth = lfo3;
    lfo4Depth = lfo4;
}

void ModRouting::updateModValues(float adsr)
{
    modAdsrSample = adsr;
}

void ModRouting::setRoutingState(const RoutingState& newState)
{
    paramMins = newState.mins;
    paramMaxs = newState.maxs;
    modMultiplier = newState.multiplier;
    modState = newState.onOffState;
    modAroundVal = newState.aroundVal;
    currentRoute = newState.route;
    usedRoutes = newState.used;
}

ModRouting::RoutingState ModRouting::getRoutingState()
{
    RoutingState returnState;
    returnState.mins = paramMins;
    returnState.maxs = paramMaxs;
    returnState.multiplier = modMultiplier;
    returnState.onOffState = modState;
    returnState.aroundVal = modAroundVal;
    returnState.route = currentRoute;
    returnState.used = usedRoutes;

    return returnState;
}

float ModRouting::getRangeWidth(float minimum, float maximum)
{
    return maximum - minimum;
}

float ModRouting::getModMultiplier(int modIndex, float range, bool modAroundValue)
{
    if (modAroundValue)
    {
        return range / 2;
    }
    else return range;
}

void ModRouting::setCurrentRoutes(int lfoRoute, int lfoIndex)
{
    int lfoArrayIndex = lfoIndex - 1;
    if (lfoRoute != 0)
    for (int i = 0; i < paramNumber; i++)
    {
        if (lfoRoute == i)
        {
            modState[i] = true;
            currentRoute[i] = lfoIndex;
            usedRoutes[lfoArrayIndex] = i;
        }
        else if(!isUsedRoute(lfoRoute)) modState[i] = false;
    }
}

float ModRouting::modulateValue(int modIndex, float currentValue)
{
    if (modAroundVal[modIndex]) modMultiplier[modIndex] =
        std::min
        (
            (currentValue - paramMins[modIndex]), (paramMaxs[modIndex] - currentValue)
        );
    else modMultiplier[modIndex] = currentValue - paramMins[modIndex];
    if (modState[modIndex]) return getModulatedValue(modIndex, currentValue);
    else return currentValue;
}

float ModRouting::getModulatedValue(int modIndex, float currentValue)
{
    switch (currentRoute[modIndex])
    {
    case 1:
        if (modAroundVal[modIndex])
            return getLimitedAroundValue(modIndex, currentValue, lfo1Sample, lfo1Depth);
        else
            return getLimitedBelowValue(modIndex, currentValue, lfo1Sample, lfo1Depth);
    case 2:
        if (modAroundVal[modIndex])
            return getLimitedAroundValue(modIndex, currentValue, lfo2Sample, lfo2Depth);
        else
            return getLimitedBelowValue(modIndex, currentValue, lfo2Sample, lfo2Depth);
    case 3:
        if (modAroundVal[modIndex])
            return getLimitedAroundValue(modIndex, currentValue, lfo3Sample, lfo3Depth);
        else
            return getLimitedBelowValue(modIndex, currentValue, lfo3Sample, lfo3Depth);
    case 4:
        if (modAroundVal[modIndex])
            return getLimitedAroundValue(modIndex, currentValue, lfo4Sample, lfo4Depth);
        else
            return getLimitedBelowValue(modIndex, currentValue, lfo4Sample, lfo4Depth);
    case 5:
        return std::max(paramMins[modIndex], std::min(paramMaxs[modIndex], currentValue * modAdsrSample));
    default:
            assert(false);
        break;
    }
}

float ModRouting::getLimitedAroundValue(int modIndex, float currentValue, float& modSample, float modDepth)
{
    return std::max(paramMins[modIndex], std::min(paramMaxs[modIndex], 
        currentValue + (modSample * modDepth * modMultiplier[modIndex])
    ));
}

float ModRouting::getLimitedBelowValue(int modIndex, float currentValue, float& modSample, float modDepth)
{
    return std::max(paramMins[modIndex], std::min(paramMaxs[modIndex], 
        currentValue - modDepth * (((modSample * modMultiplier[modIndex]) + modMultiplier[modIndex]) / 2)
    ));  
}

bool ModRouting::isUsedRoute(int routeIndex)
{
    for (int i = 0; i < usedRoutes.size(); i++)
    {
        if (usedRoutes[i] == routeIndex) return true;
    }
    return false;
}
