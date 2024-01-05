#include <tuple>
#include <iostream>
#include <string.h>
#include <fstream>
#include <regex>
#include <tuple>

using namespace std;

long getRelation(vector<vector<long>> mapValues, long val) {
    for (auto& entry : mapValues) {
        long source = entry[1];
        long dest = entry[0];
        long range = entry[2];
        if ((val - source) <= range && val >= source) return dest + val - source;
    }
    return val;
}

int main(int agrc, char** argv) {
    ifstream stream("input.txt");
    string line;
    vector<long> seeds;
    regex seedRegex("(\\d+)");
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
                seeds.push_back(stol(seedRegexMatch[0]));
                lineIter = seedRegexMatch.suffix().first;
            }
        }
        else if (currLine >= seedToSoilRange.first && currLine <= seedToSoilRange.second) // And every other line
        {
            regex_search(line.begin(), line.end(), mapRegexMatch, mapRegex);
            // cout << mapRegexMatch[1] << ' ' << mapRegexMatch[2] << ' ' << mapRegexMatch[3] << '\n';
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
    long lowestLocation = LONG_MAX;
    for (auto seed : seeds) {
        long seedToSoilMap = getRelation(seedToSoil, seed);
        long soilToFertilizerMap = getRelation(soilToFertilizer, seedToSoilMap);
        long fertilizerToWaterMap = getRelation(fertilizerToWater, soilToFertilizerMap);
        long waterToLightMap = getRelation(waterToLight, fertilizerToWaterMap);
        long lightToTemperatureMap = getRelation(lightToTemperature, waterToLightMap);
        long temperatureToHumidityMap = getRelation(temperatureToHumidity, lightToTemperatureMap);
        long humidityToLocationMap = getRelation(humidityToLocation, temperatureToHumidityMap);
        cout << "Seed " << seed << " location " << humidityToLocationMap << '\n';
        lowestLocation = min(lowestLocation, humidityToLocationMap);
    }
    cout << lowestLocation ;
    // for (auto i : seedToSoil) cout << i[0] ;
}