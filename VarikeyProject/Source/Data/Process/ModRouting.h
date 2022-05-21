/*
  ==============================================================================

    ModRouting.h
    Created: 20 May 2022 8:43:53pm
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include<iostream>
#include<cmath>
#include<array>
#include<vector>
#include<string>

class ModRouting
{
public:
    ModRouting() {};

    void setInModList(int modIndex, float paramMin, float paramMax, bool modAroundValue);

    float modulateValue(int modIndex, float currentValue);

    void updateModRoutes(int lfo1, int lfo2, int lfo3, int lfo4, int adsr);
    void updateModValues(float lfo1, float lfo2, float lfo3, float lfo4);
    void updateModDepth(float lfo1, float lfo2, float lfo3, float lfo4);
    void updateModValues(float &adsr);

private:

    static const int paramNumber = 20;

    float getRangeWidth(float minimum, float maximum);
    float getModMultiplier(int modIndex, float range, bool modAroundValue);
    void setCurrentRoutes(int lfoRoute, int lfoIndex);
    float getModulatedValue(int modIndex, float currentValue);
    float getLimitedAroundValue(int modIndex, float currentValue, float& modSample, float modDepth);
    float getLimitedBelowValue(int modIndex, float currentValue, float& modSample, float modDepth);
    bool isUsedRoute(int routeIndex);

    std::array<float, paramNumber> paramMins{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    std::array<float, paramNumber> paramMaxs{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    std::array<float, paramNumber> modMultiplier{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    std::array<bool, paramNumber> modState{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    std::array<bool, paramNumber> modAroundVal{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    std::array<int, paramNumber> currentRoute{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    std::array<int, 5> usedRoutes{ 0, 0, 0, 0, 0 };

    int lfo1Route = 0;
    float lfo1Sample = 0;
    float lfo1Depth = 0;

    int lfo2Route = 0;
    float lfo2Sample = 0;
    float lfo2Depth = 0;

    int lfo3Route = 0;
    float lfo3Sample = 0;
    float lfo3Depth = 0;

    int lfo4Route = 0;
    float lfo4Sample = 0;
    float lfo4Depth = 0;

    int modAdsrRoute = 0;
    float modAdsrSample = 0;


};