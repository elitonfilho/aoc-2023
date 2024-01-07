#include <tuple>
#include <iostream>
#include <string.h>
#include <fstream>
#include <regex>
#include <tuple>

using namespace std;

long getInverseRelation(vector<vector<long>> mapValues, long val) {
    for (auto& entry : mapValues) {
        long source = entry[0];
        long dest = entry[1];
        long range = entry[2];
        if ((val - source) <= range && val >= source) return dest + val - source;
    }
    return val;
}

bool checkIfSeedExists(vector<long>& seeds, long val) {
    for (int i = 0; i < seeds.size(); i += 2) {
        long initialSeed = seeds[i];
        long range = seeds[i + 1];
        if ((val - initialSeed) < range && (val - initialSeed) >= 0){
             return true ;
        }
    }
    return false;
}

// Strategy 2: find the link between location -> seed and then check if the seed exists
// Starting from the lowest location (0 -> max location)
int main(int agrc, char** argv) {
    ifstream stream("input.txt");
    string line;
    vector<long> seeds;
    regex seedRegex("(\\d+) (\\d+)");
    regex mapRegex("(\\d+) (\\d+) (\\d+)");
    match_results<string::iterator> seedRegexMatch;
    match_results<string::iterator> mapRegexMatch;
    // Line ranges
    auto seedToSoilRange = make_pair<int, int>(3, 18);
    auto soilToFertilizerRange = make_pair<int, int>(21, 33);
    auto fertilizerToWaterRange = make_pair<int, int>(36, 57);
    auto waterToLightRange = make_pair<int, int>(60, 105);
    auto lightToTemperatureRange = make_pair<int, int>(108, 133);
    auto temperatureToHumidityRange = make_pair<int, int>(136, 157);
    auto humidityToLocationRange = make_pair<int, int>(160, 207);

    vector<vector<long>> seedToSoil;
    vector<vector<long>> soilToFertilizer;
    vector<vector<long>> fertilizerToWater;
    vector<vector<long>> waterToLight;
    vector<vector<long>> lightToTemperature;
    vector<vector<long>> temperatureToHumidity;
    vector<vector<long>> humidityToLocation;

    int currLine = 0;
    while (getline(stream, line)) {
        if (currLine == 0) { // Parsing seeds
            string::iterator lineIter = line.begin();
            while (regex_search(lineIter, line.end(), seedRegexMatch, seedRegex)) {
                long curSeed = stol(seedRegexMatch[1]);
                long seedRange = stol(seedRegexMatch[2]);
                seeds.push_back(curSeed);
                seeds.push_back(seedRange);
                lineIter = seedRegexMatch.suffix().first;
            }
        }
        else if (currLine >= seedToSoilRange.first && currLine <= seedToSoilRange.second) // And every other line
        {
            regex_search(line.begin(), line.end(), mapRegexMatch, mapRegex);
            seedToSoil.push_back(vector<long> {stol(mapRegexMatch[1]), stol(mapRegexMatch[2]), stol(mapRegexMatch[3])});
        }
        else if (currLine >= soilToFertilizerRange.first && currLine <= soilToFertilizerRange.second) {
            regex_search(line.begin(), line.end(), mapRegexMatch, mapRegex);
            soilToFertilizer.push_back(vector<long> {stol(mapRegexMatch[1]), stol(mapRegexMatch[2]), stol(mapRegexMatch[3])});
        }
        else if (currLine >= fertilizerToWaterRange.first && currLine <= fertilizerToWaterRange.second) {
            regex_search(line.begin(), line.end(), mapRegexMatch, mapRegex);
            fertilizerToWater.push_back(vector<long> {stol(mapRegexMatch[1]), stol(mapRegexMatch[2]), stol(mapRegexMatch[3])});
        }
        else if (currLine >= waterToLightRange.first && currLine <= waterToLightRange.second) {
            regex_search(line.begin(), line.end(), mapRegexMatch, mapRegex);
            waterToLight.push_back(vector<long> {stol(mapRegexMatch[1]), stol(mapRegexMatch[2]), stol(mapRegexMatch[3])});
        }
        else if (currLine >= lightToTemperatureRange.first && currLine <= lightToTemperatureRange.second) {
            regex_search(line.begin(), line.end(), mapRegexMatch, mapRegex);
            lightToTemperature.push_back(vector<long> {stol(mapRegexMatch[1]), stol(mapRegexMatch[2]), stol(mapRegexMatch[3])});
        }
        else if (currLine >= temperatureToHumidityRange.first && currLine <= temperatureToHumidityRange.second) {
            regex_search(line.begin(), line.end(), mapRegexMatch, mapRegex);
            temperatureToHumidity.push_back(vector<long> {stol(mapRegexMatch[1]), stol(mapRegexMatch[2]), stol(mapRegexMatch[3])});
        }
        else if (currLine >= humidityToLocationRange.first && currLine <= humidityToLocationRange.second) {
            regex_search(line.begin(), line.end(), mapRegexMatch, mapRegex);
            humidityToLocation.push_back(vector<long> {stol(mapRegexMatch[1]), stol(mapRegexMatch[2]), stol(mapRegexMatch[3])});
        }
        currLine++;
    }

    // Implementing logic
    // Ideally we should use LONG_MAX, but INT_MAX should suffice
    for (int i = 0; i < INT_MAX; i++) {
        long humidityToLocationMap = getInverseRelation(humidityToLocation, i);
        long temperatureToHumidityMap = getInverseRelation(temperatureToHumidity, humidityToLocationMap);
        long lightToTemperatureMap = getInverseRelation(lightToTemperature, temperatureToHumidityMap);
        long waterToLightMap = getInverseRelation(waterToLight, lightToTemperatureMap);
        long fertilizerToWaterMap = getInverseRelation(fertilizerToWater, waterToLightMap);
        long soilToFertilizerMap = getInverseRelation(soilToFertilizer, fertilizerToWaterMap);
        long seedToSoilMap = getInverseRelation(seedToSoil, soilToFertilizerMap);
        if (checkIfSeedExists(seeds, seedToSoilMap)) {
            cout << i << " Soil to Seed " << seedToSoilMap << '\n';
            cout << i << " Fertilizer to Soil " << soilToFertilizerMap << '\n';
            cout << i << " Water to fertilizer " << fertilizerToWaterMap << '\n';
            cout << i << " Light to water " << waterToLightMap << '\n';
            cout << i << " Temperature to Light " << lightToTemperatureMap << '\n';
            cout << i << " Humidity to Temperature " << temperatureToHumidityMap << '\n';
            cout << i << " Location to Humidity " << humidityToLocationMap << '\n';
            cout << "Result: " << i - 1 << '\n';
            break;
        }
    }
}