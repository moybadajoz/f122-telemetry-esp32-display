
struct PacketHeader {
  uint16_t m_packetFormat; // 2022
  uint8_t m_gameMajorVersion; // Game major version - "X.00"
  uint8_t m_gameMinorVersion; // Game minor version - "1.XX"
  uint8_t m_packetVersion; // Version of this packet type, all start from 1
  uint8_t m_packetId; // Identifier for the packet type, see below
  uint64_t m_sessionUID; // Unique identifier for the session
  float m_sessionTime; // Session timestamp
  uint32_t m_frameIdentifier; // Identifier for the frame the data was retrieved on
  uint8_t m_playerCarIndex; // Index of player's car in the array
  uint8_t m_secondaryPlayerCarIndex; // Index of secondary player's car in the array (splitscreen)
  // 255 if no second player
  unsigned long get(char* buffer){
    unsigned long offset = 0;
    memcpy(&this->m_packetFormat,&buffer[offset],sizeof(this->m_packetFormat));
    offset = offset + sizeof(this->m_packetFormat);
    memcpy(&this->m_gameMajorVersion,&buffer[offset],sizeof(this->m_gameMajorVersion));
    offset = offset + sizeof(this->m_gameMajorVersion);
    memcpy(&this->m_gameMinorVersion,&buffer[offset],sizeof(this->m_gameMinorVersion));
    offset = offset + sizeof(this->m_gameMinorVersion);
    memcpy(&this->m_packetVersion,&buffer[offset],sizeof(this->m_packetVersion));
    offset = offset + sizeof(this->m_packetVersion);
    memcpy(&this->m_packetId,&buffer[offset],sizeof(this->m_packetId));
    offset = offset + sizeof(this->m_packetId);
    memcpy(&this->m_sessionUID,&buffer[offset],sizeof(this->m_sessionUID));
    offset = offset + sizeof(this->m_sessionUID);        
    memcpy(&this->m_sessionTime,&buffer[offset],sizeof(this->m_sessionTime));
    offset = offset + sizeof(this->m_sessionTime);
    memcpy(&this->m_frameIdentifier,&buffer[offset],sizeof(this->m_frameIdentifier));
    offset = offset + sizeof(this->m_frameIdentifier);
    memcpy(&this->m_playerCarIndex,&buffer[offset],sizeof(this->m_playerCarIndex));
    offset = offset + sizeof(this->m_playerCarIndex);
    memcpy(&this->m_secondaryPlayerCarIndex,&buffer[offset],sizeof(this->m_secondaryPlayerCarIndex));
    offset = offset + sizeof(this->m_secondaryPlayerCarIndex);

    return offset;
  }
};

struct CarMotionData {
  float m_worldPositionX; // World space X position
  float m_worldPositionY; // World space Y position
  float m_worldPositionZ; // World space Z position
  float m_worldVelocityX; // Velocity in world space X
  float m_worldVelocityY; // Velocity in world space Y
  float m_worldVelocityZ; // Velocity in world space Z
  int16_t m_worldForwardDirX; // World space forward X direction (normalised)
  int16_t m_worldForwardDirY; // World space forward Y direction (normalised)
  int16_t m_worldForwardDirZ; // World space forward Z direction (normalised)
  int16_t m_worldRightDirX; // World space right X direction (normalised)
  int16_t m_worldRightDirY; // World space right Y direction (normalised)
  int16_t m_worldRightDirZ; // World space right Z direction (normalised)
  float m_gForceLateral; // Lateral G-Force component
  float m_gForceLongitudinal; // Longitudinal G-Force component
  float m_gForceVertical; // Vertical G-Force component
  float m_yaw; // Yaw angle in radians
  float m_pitch; // Pitch angle in radians
  float m_roll; // Roll angle in radians

  unsigned long get(char* buffer, unsigned long offset) {
    // WorldPosition
    memcpy(&this->m_worldPositionX, &buffer[offset], sizeof(m_worldPositionX));
    offset = offset + sizeof(m_worldPositionX);
    memcpy(&this->m_worldPositionY, &buffer[offset], sizeof(m_worldPositionY));
    offset = offset + sizeof(m_worldPositionY);
    memcpy(&this->m_worldPositionZ, &buffer[offset], sizeof(m_worldPositionZ));
    offset = offset + sizeof(m_worldPositionZ);
    // WorldVelocity
    memcpy(&this->m_worldVelocityX, &buffer[offset], sizeof(m_worldVelocityX));
    offset = offset + sizeof(m_worldVelocityX);
    memcpy(&this->m_worldVelocityY, &buffer[offset], sizeof(m_worldVelocityY));
    offset = offset + sizeof(m_worldVelocityY);
    memcpy(&this->m_worldVelocityZ, &buffer[offset], sizeof(m_worldVelocityZ));
    offset = offset + sizeof(m_worldVelocityZ);
    // WorldForwardDir
    memcpy(&this->m_worldForwardDirX, &buffer[offset], sizeof(m_worldForwardDirX));
    offset = offset + sizeof(m_worldForwardDirX);
    memcpy(&this->m_worldForwardDirY, &buffer[offset], sizeof(m_worldForwardDirY));
    offset = offset + sizeof(m_worldForwardDirY);
    memcpy(&this->m_worldForwardDirZ, &buffer[offset], sizeof(m_worldForwardDirZ));
    offset = offset + sizeof(m_worldForwardDirZ);
    // WorldRightDir
    memcpy(&this->m_worldRightDirX, &buffer[offset], sizeof(m_worldRightDirX));
    offset = offset + sizeof(m_worldRightDirX);
    memcpy(&this->m_worldRightDirY, &buffer[offset], sizeof(m_worldRightDirY));
    offset = offset + sizeof(m_worldRightDirY);
    memcpy(&this->m_worldRightDirZ, &buffer[offset], sizeof(m_worldRightDirZ));
    offset = offset + sizeof(m_worldRightDirZ);
    // gForce
    memcpy(&this->m_gForceLateral, &buffer[offset], sizeof(m_gForceLateral));
    offset = offset + sizeof(m_gForceLateral);
    memcpy(&this->m_gForceLongitudinal, &buffer[offset], sizeof(m_gForceLongitudinal));
    offset = offset + sizeof(m_gForceLongitudinal);
    memcpy(&this->m_gForceVertical, &buffer[offset], sizeof(m_gForceVertical));
    offset = offset + sizeof(m_gForceVertical);
    // Angles
    memcpy(&this->m_yaw, &buffer[offset], sizeof(m_yaw));
    offset = offset + sizeof(m_yaw);
    memcpy(&this->m_pitch, &buffer[offset], sizeof(m_pitch));
    offset = offset + sizeof(m_pitch);
    memcpy(&this->m_roll, &buffer[offset], sizeof(m_roll));
    offset = offset + sizeof(m_roll);
        //
        return offset;
    }
};

struct PacketMotionData {
  PacketHeader m_header; // Header
  CarMotionData m_carMotionData[22]; // Data for all cars on track
  // Extra player car ONLY data
  float m_suspensionPosition[4]; // Note: All wheel arrays have the following order:
  float m_suspensionVelocity[4]; // RL, RR, FL, FR
  float m_suspensionAcceleration[4]; // RL, RR, FL, FR
  float m_wheelSpeed[4]; // Speed of each wheel
  float m_wheelSlip[4]; // Slip ratio for each wheel
  float m_localVelocityX; // Velocity in local space
  float m_localVelocityY; // Velocity in local space
  float m_localVelocityZ; // Velocity in local space
  float m_angularVelocityX; // Angular velocity x-component
  float m_angularVelocityY; // Angular velocity y-component
  float m_angularVelocityZ; // Angular velocity z-component
  float m_angularAccelerationX; // Angular velocity x-component
  float m_angularAccelerationY; // Angular velocity y-component
  float m_angularAccelerationZ; // Angular velocity z-component
  float m_frontWheelsAngle; // Current front wheels angle in radians

  void get(char* buffer) {
    // WorldPosition
    unsigned long offset = this->m_header.get(buffer);
    for (int i = 0; i < 22; i++) {
      offset = this->m_carMotionData[i].get(buffer, offset);
    }
    // Suspensions
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_suspensionPosition[i], &buffer[offset], sizeof(this->m_suspensionPosition[i]));
      offset = offset + sizeof(this->m_suspensionPosition[i]);
    }
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_suspensionVelocity[i], &buffer[offset], sizeof(this->m_suspensionVelocity[i]));
      offset = offset + sizeof(this->m_suspensionVelocity[i]);
    }
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_suspensionAcceleration[i], &buffer[offset], sizeof(this->m_suspensionAcceleration[i]));
      offset = offset + sizeof(this->m_suspensionAcceleration[i]);
    }
    // Wheels
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_wheelSpeed[i], &buffer[offset], sizeof(this->m_wheelSpeed[i]));
      offset = offset + sizeof(this->m_wheelSpeed[i]);
    }
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_wheelSlip[i], &buffer[offset], sizeof(this->m_wheelSlip[i]));
      offset = offset + sizeof(this->m_wheelSlip[i]);
    }
    // localVelocity
    memcpy(&this->m_localVelocityX, &buffer[offset], sizeof(m_localVelocityX));
    offset = offset + sizeof(m_localVelocityX);
    memcpy(&this->m_localVelocityY, &buffer[offset], sizeof(m_localVelocityY));
    offset = offset + sizeof(m_localVelocityY);
    memcpy(&this->m_localVelocityZ, &buffer[offset], sizeof(m_localVelocityZ));
    offset = offset + sizeof(m_localVelocityZ);
    // angularVelocity
    memcpy(&this->m_angularVelocityX, &buffer[offset], sizeof(m_angularVelocityX));
    offset = offset + sizeof(m_angularVelocityX);
    memcpy(&this->m_angularVelocityY, &buffer[offset], sizeof(m_angularVelocityY));
    offset = offset + sizeof(m_angularVelocityY);
    memcpy(&this->m_angularVelocityZ, &buffer[offset], sizeof(m_angularVelocityZ));
    offset = offset + sizeof(m_angularVelocityZ);
    // angularAcceleration
    memcpy(&this->m_angularAccelerationX, &buffer[offset], sizeof(m_angularAccelerationX));
    offset = offset + sizeof(m_angularAccelerationX);
    memcpy(&this->m_angularAccelerationY, &buffer[offset], sizeof(m_angularAccelerationY));
    offset = offset + sizeof(m_angularAccelerationY);
    memcpy(&this->m_angularAccelerationZ, &buffer[offset], sizeof(m_angularAccelerationZ));
    offset = offset + sizeof(m_angularAccelerationZ);
    memcpy(&this->m_frontWheelsAngle, &buffer[offset], sizeof(m_frontWheelsAngle));
    offset = offset + sizeof(m_frontWheelsAngle);
  }
};

struct MarshalZone {
  float m_zoneStart; // Fraction (0..1) of way through the lap the marshal zone starts
  int8_t m_zoneFlag; // -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow, 4 = red

  unsigned long get(char* buffer, unsigned long offset) {
    memcpy(&this->m_zoneStart, &buffer[offset], sizeof(m_zoneStart));
    offset = offset + sizeof(m_zoneStart);
    memcpy(&this->m_zoneFlag, &buffer[offset], sizeof(m_zoneFlag));
    offset = offset + sizeof(m_zoneFlag);

    return offset;
    }
};

struct WeatherForecastSample {
  uint8_t m_sessionType; // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1
  // 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ, 10 = R, 11 = R2
  // 12 = R3, 13 = Time Trial
  uint8_t m_timeOffset; // Time in minutes the forecast is for
  uint8_t m_weather; // Weather - 0 = clear, 1 = light cloud, 2 = overcast
  // 3 = light rain, 4 = heavy rain, 5 = storm
  int8_t m_trackTemperature; // Track temp. in degrees Celsius
  int8_t m_trackTemperatureChange; // Track temp. change – 0 = up, 1 = down, 2 = no change
  int8_t m_airTemperature; // Air temp. in degrees celsius
  int8_t m_airTemperatureChange; // Air temp. change – 0 = up, 1 = down, 2 = no change
  uint8_t m_rainPercentage; // Rain percentage (0-100)

  unsigned long get(char* buffer, unsigned long offset) {
    memcpy(&this->m_sessionType, &buffer[offset], sizeof(m_sessionType));
    offset = offset + sizeof(m_sessionType);
    memcpy(&this->m_timeOffset, &buffer[offset], sizeof(m_timeOffset));
    offset = offset + sizeof(m_timeOffset);
    memcpy(&this->m_weather, &buffer[offset], sizeof(m_weather));
    offset = offset + sizeof(m_weather);
    memcpy(&this->m_trackTemperature, &buffer[offset], sizeof(m_trackTemperature));
    offset = offset + sizeof(m_trackTemperature);
    memcpy(&this->m_trackTemperatureChange, &buffer[offset], sizeof(m_trackTemperatureChange));
    offset = offset + sizeof(m_trackTemperatureChange);
    memcpy(&this->m_airTemperature, &buffer[offset], sizeof(m_airTemperature));
    offset = offset + sizeof(m_airTemperature);
    memcpy(&this->m_airTemperatureChange, &buffer[offset], sizeof(m_airTemperatureChange));
    offset = offset + sizeof(m_airTemperatureChange);
    memcpy(&this->m_rainPercentage, &buffer[offset], sizeof(m_rainPercentage));
    offset = offset + sizeof(m_rainPercentage);
    
    return offset;
  }  
};
  
struct PacketSessionData {
  PacketHeader m_header; // Header
  uint8_t m_weather; // Weather - 0 = clear, 1 = light cloud, 2 = overcast
  // 3 = light rain, 4 = heavy rain, 5 = storm
  int8_t m_trackTemperature; // Track temp. in degrees celsius
  int8_t m_airTemperature; // Air temp. in degrees celsius
  uint8_t m_totalLaps; // Total number of laps in this race
  uint16_t m_trackLength; // Track length in metres
  uint8_t m_sessionType; // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P
  // 5 = Q1, 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ
  // 10 = R, 11 = R2, 12 = R3, 13 = Time Trial
  int8_t m_trackId; // -1 for unknown, see appendix
  uint8_t m_formula; // Formula, 0 = F1 Modern, 1 = F1 Classic, 2 = F2,
  // 3 = F1 Generic, 4 = Beta, 5 = Supercars
  // 6 = Esports, 7 = F2 2021
  uint16_t m_sessionTimeLeft; // Time left in session in seconds
  uint16_t m_sessionDuration; // Session duration in seconds
  uint8_t m_pitSpeedLimit; // Pit speed limit in kilometres per hour
  uint8_t m_gamePaused; // Whether the game is paused – network game only
  uint8_t m_isSpectating; // Whether the player is spectating
  uint8_t m_spectatorCarIndex; // Index of the car being spectated
  uint8_t m_sliProNativeSupport; // SLI Pro support, 0 = inactive, 1 = active
  uint8_t m_numMarshalZones; // Number of marshal zones to follow
  MarshalZone m_marshalZones[21]; // List of marshal zones – max 21
  uint8_t m_safetyCarStatus; // 0 = no safety car, 1 = full
  // 2 = virtual, 3 = formation lap
  uint8_t m_networkGame; // 0 = offline, 1 = online
  uint8_t m_numWeatherForecastSamples; // Number of weather samples to follow
  WeatherForecastSample m_weatherForecastSamples[56]; // Array of weather forecast samples
  uint8_t m_forecastAccuracy; // 0 = Perfect, 1 = Approximate
  uint8_t m_aiDifficulty; // AI Difficulty rating – 0-110
  uint32_t m_seasonLinkIdentifier; // Identifier for season - persists across saves
  uint32_t m_weekendLinkIdentifier; // Identifier for weekend - persists across saves
  uint32_t m_sessionLinkIdentifier; // Identifier for session - persists across saves
  uint8_t m_pitStopWindowIdealLap; // Ideal lap to pit on for current strategy (player)
  uint8_t m_pitStopWindowLatestLap; // Latest lap to pit on for current strategy (player)
  uint8_t m_pitStopRejoinPosition; // Predicted position to rejoin at (player)
  uint8_t m_steeringAssist; // 0 = off, 1 = on
  uint8_t m_brakingAssist; // 0 = off, 1 = low, 2 = medium, 3 = high
  uint8_t m_gearboxAssist; // 1 = manual, 2 = manual & suggested gear, 3 = auto
  uint8_t m_pitAssist; // 0 = off, 1 = on
  uint8_t m_pitReleaseAssist; // 0 = off, 1 = on
  uint8_t m_ERSAssist; // 0 = off, 1 = on
  uint8_t m_DRSAssist; // 0 = off, 1 = on
  uint8_t m_dynamicRacingLine; // 0 = off, 1 = corners only, 2 = full
  uint8_t m_dynamicRacingLineType; // 0 = 2D, 1 = 3D
  uint8_t m_gameMode; // Game mode id - see appendix
  uint8_t m_ruleSet; // Ruleset - see appendix
  uint32_t m_timeOfDay; // Local time of day - minutes since midnight
  uint8_t m_sessionLength; // 0 = None, 2 = Very Short, 3 = Short, 4 = Medium
 // 5 = Medium Long, 6 = Long, 7 = Full
  void get(char* buffer) {
    unsigned long offset = this->m_header.get(buffer);
    memcpy(&this->m_weather, &buffer[offset], sizeof(m_weather));
    offset = offset + sizeof(m_weather);
    memcpy(&this->m_trackTemperature, &buffer[offset], sizeof(m_trackTemperature));
    offset = offset + sizeof(m_trackTemperature);
    memcpy(&this->m_airTemperature, &buffer[offset], sizeof(m_airTemperature));
    offset = offset + sizeof(m_airTemperature);
    memcpy(&this->m_totalLaps, &buffer[offset], sizeof(m_totalLaps));
    offset = offset + sizeof(m_totalLaps);
    memcpy(&this->m_trackLength, &buffer[offset], sizeof(m_trackLength));
    offset = offset + sizeof(m_trackLength);
    memcpy(&this->m_sessionType, &buffer[offset], sizeof(m_sessionType));
    offset = offset + sizeof(m_sessionType);
    memcpy(&this->m_trackId, &buffer[offset], sizeof(m_trackId));
    offset = offset + sizeof(m_trackId);
    memcpy(&this->m_formula, &buffer[offset], sizeof(m_formula));
    offset = offset + sizeof(m_formula);
    memcpy(&this->m_sessionTimeLeft, &buffer[offset], sizeof(m_sessionTimeLeft));
    offset = offset + sizeof(m_sessionTimeLeft);
    memcpy(&this->m_sessionDuration, &buffer[offset], sizeof(m_sessionDuration));
    offset = offset + sizeof(m_sessionDuration);
    memcpy(&this->m_pitSpeedLimit, &buffer[offset], sizeof(m_pitSpeedLimit));
    offset = offset + sizeof(m_pitSpeedLimit);
    memcpy(&this->m_gamePaused, &buffer[offset], sizeof(m_gamePaused));
    offset = offset + sizeof(m_gamePaused);
    memcpy(&this->m_isSpectating, &buffer[offset], sizeof(m_isSpectating));
    offset = offset + sizeof(m_isSpectating);
    memcpy(&this->m_spectatorCarIndex, &buffer[offset], sizeof(m_spectatorCarIndex));
    offset = offset + sizeof(m_spectatorCarIndex);
    memcpy(&this->m_sliProNativeSupport, &buffer[offset], sizeof(m_sliProNativeSupport));
    offset = offset + sizeof(m_sliProNativeSupport);
    memcpy(&this->m_numMarshalZones, &buffer[offset], sizeof(m_numMarshalZones));
    offset = offset + sizeof(m_numMarshalZones);
    for (int i = 0; i < this->m_numMarshalZones; i++) {
        offset = this->m_marshalZones[i].get(buffer, offset);
    }
    memcpy(&this->m_safetyCarStatus, &buffer[offset], sizeof(m_safetyCarStatus));
    offset = offset + sizeof(m_safetyCarStatus);
    memcpy(&this->m_networkGame, &buffer[offset], sizeof(m_networkGame));
    offset = offset + sizeof(m_networkGame);
    memcpy(&this->m_numWeatherForecastSamples, &buffer[offset], sizeof(m_numWeatherForecastSamples));
    offset = offset + sizeof(m_numWeatherForecastSamples);
    for (int i = 0; i < this->m_numWeatherForecastSamples; i++) {
        offset = this->m_weatherForecastSamples[i].get(buffer, offset);
    }
    memcpy(&this->m_forecastAccuracy, &buffer[offset], sizeof(m_forecastAccuracy));
    offset = offset + sizeof(m_forecastAccuracy);
    memcpy(&this->m_aiDifficulty, &buffer[offset], sizeof(m_aiDifficulty));
    offset = offset + sizeof(m_aiDifficulty);
    memcpy(&this->m_seasonLinkIdentifier, &buffer[offset], sizeof(m_seasonLinkIdentifier));
    offset = offset + sizeof(m_seasonLinkIdentifier);
    memcpy(&this->m_weekendLinkIdentifier, &buffer[offset], sizeof(m_weekendLinkIdentifier));
    offset = offset + sizeof(m_weekendLinkIdentifier);
    memcpy(&this->m_sessionLinkIdentifier, &buffer[offset], sizeof(m_sessionLinkIdentifier));
    offset = offset + sizeof(m_sessionLinkIdentifier);
    memcpy(&this->m_pitStopWindowIdealLap, &buffer[offset], sizeof(m_pitStopWindowIdealLap));
    offset = offset + sizeof(m_pitStopWindowIdealLap);
    memcpy(&this->m_pitStopWindowLatestLap, &buffer[offset], sizeof(m_pitStopWindowLatestLap));
    offset = offset + sizeof(m_pitStopWindowLatestLap);
    memcpy(&this->m_pitStopRejoinPosition, &buffer[offset], sizeof(m_pitStopRejoinPosition));
    offset = offset + sizeof(m_pitStopRejoinPosition);
    memcpy(&this->m_steeringAssist, &buffer[offset], sizeof(m_steeringAssist));
    offset = offset + sizeof(m_steeringAssist);
    memcpy(&this->m_brakingAssist, &buffer[offset], sizeof(m_brakingAssist));
    offset = offset + sizeof(m_brakingAssist);
    memcpy(&this->m_gearboxAssist, &buffer[offset], sizeof(m_gearboxAssist));
    offset = offset + sizeof(m_gearboxAssist);
    memcpy(&this->m_pitAssist, &buffer[offset], sizeof(m_pitAssist));
    offset = offset + sizeof(m_pitAssist);
    memcpy(&this->m_pitReleaseAssist, &buffer[offset], sizeof(m_pitReleaseAssist));
    offset = offset + sizeof(m_pitReleaseAssist);
    memcpy(&this->m_ERSAssist, &buffer[offset], sizeof(m_ERSAssist));
    offset = offset + sizeof(m_ERSAssist);
    memcpy(&this->m_DRSAssist, &buffer[offset], sizeof(m_DRSAssist));
    offset = offset + sizeof(m_DRSAssist);
    memcpy(&this->m_dynamicRacingLine, &buffer[offset], sizeof(m_dynamicRacingLine));
    offset = offset + sizeof(m_dynamicRacingLine);
    memcpy(&this->m_dynamicRacingLineType, &buffer[offset], sizeof(m_dynamicRacingLineType));
    offset = offset + sizeof(m_dynamicRacingLineType);
    memcpy(&this->m_gameMode, &buffer[offset], sizeof(m_gameMode));
    offset = offset + sizeof(m_gameMode);
    memcpy(&this->m_ruleSet, &buffer[offset], sizeof(m_ruleSet));
    offset = offset + sizeof(m_ruleSet);
    memcpy(&this->m_timeOfDay, &buffer[offset], sizeof(m_timeOfDay));
    offset = offset + sizeof(m_timeOfDay);
    memcpy(&this->m_sessionLength, &buffer[offset], sizeof(m_sessionLength));
    offset = offset + sizeof(m_sessionLength);
  }

};

struct LapData {
  uint32_t m_lastLapTimeInMS; // Last lap time in milliseconds
  uint32_t m_currentLapTimeInMS; // Current time around the lap in milliseconds
  uint16_t m_sector1TimeInMS; // Sector 1 time in milliseconds
  uint16_t m_sector2TimeInMS; // Sector 2 time in milliseconds
  float m_lapDistance; // Distance vehicle is around current lap in metres – could
  // be negative if line hasn’t been crossed yet
  float m_totalDistance; // Total distance travelled in session in metres – could
  // be negative if line hasn’t been crossed yet
  float m_safetyCarDelta; // Delta in seconds for safety car
  uint8_t m_carPosition; // Car race position
  uint8_t m_currentLapNum; // Current lap number
  uint8_t m_pitStatus; // 0 = none, 1 = pitting, 2 = in pit area
  uint8_t m_numPitStops; // Number of pit stops taken in this race
  uint8_t m_sector; // 0 = sector1, 1 = sector2, 2 = sector3
  uint8_t m_currentLapInvalid; // Current lap invalid - 0 = valid, 1 = invalid
  uint8_t m_penalties; // Accumulated time penalties in seconds to be added
  uint8_t m_warnings; // Accumulated number of warnings issued
  uint8_t m_numUnservedDriveThroughPens; // Num drive through pens left to serve
  uint8_t m_numUnservedStopGoPens; // Num stop go pens left to serve
  uint8_t m_gridPosition; // Grid position the vehicle started the race in
  uint8_t m_driverStatus; // Status of driver - 0 = in garage, 1 = flying lap
  // 2 = in lap, 3 = out lap, 4 = on track
  uint8_t m_resultStatus; // Result status - 0 = invalid, 1 = inactive, 2 = active
  // 3 = finished, 4 = didnotfinish, 5 = disqualified
  // 6 = not classified, 7 = retired
  uint8_t m_pitLaneTimerActive; // Pit lane timing, 0 = inactive, 1 = active
  uint16_t m_pitLaneTimeInLaneInMS; // If active, the current time spent in the pit lane in ms
  uint16_t m_pitStopTimerInMS; // Time of the actual pit stop in ms
  uint8_t m_pitStopShouldServePen; // Whether the car should serve a penalty at this stop
  
  unsigned long get(char* buffer,unsigned long offset){
    memcpy(&this->m_lastLapTimeInMS, &buffer[offset], sizeof(this->m_lastLapTimeInMS));
    offset += sizeof(this->m_lastLapTimeInMS);
    memcpy(&this->m_currentLapTimeInMS, &buffer[offset], sizeof(this->m_currentLapTimeInMS));
    offset += sizeof(this->m_currentLapTimeInMS);
    memcpy(&this->m_sector1TimeInMS, &buffer[offset], sizeof(this->m_sector1TimeInMS));
    offset += sizeof(this->m_sector1TimeInMS);
    memcpy(&this->m_sector2TimeInMS, &buffer[offset], sizeof(this->m_sector2TimeInMS));
    offset += sizeof(this->m_sector2TimeInMS);
    memcpy(&this->m_lapDistance, &buffer[offset], sizeof(this->m_lapDistance));
    offset += sizeof(this->m_lapDistance);
    memcpy(&this->m_totalDistance, &buffer[offset], sizeof(this->m_totalDistance));
    offset += sizeof(this->m_totalDistance);
    memcpy(&this->m_safetyCarDelta, &buffer[offset], sizeof(this->m_safetyCarDelta));
    offset += sizeof(this->m_safetyCarDelta);
    memcpy(&this->m_carPosition, &buffer[offset], sizeof(this->m_carPosition));
    offset += sizeof(this->m_carPosition);
    memcpy(&this->m_currentLapNum, &buffer[offset], sizeof(this->m_currentLapNum));
    offset += sizeof(this->m_currentLapNum);
    memcpy(&this->m_pitStatus, &buffer[offset], sizeof(this->m_pitStatus));
    offset += sizeof(this->m_pitStatus);
    memcpy(&this->m_numPitStops, &buffer[offset], sizeof(this->m_numPitStops));
    offset += sizeof(this->m_numPitStops);
    memcpy(&this->m_sector, &buffer[offset], sizeof(this->m_sector));
    offset += sizeof(this->m_sector);
    memcpy(&this->m_currentLapInvalid, &buffer[offset], sizeof(this->m_currentLapInvalid));
    offset += sizeof(this->m_currentLapInvalid);
    memcpy(&this->m_penalties, &buffer[offset], sizeof(this->m_penalties));
    offset += sizeof(this->m_penalties);
    memcpy(&this->m_warnings, &buffer[offset], sizeof(this->m_warnings));
    offset += sizeof(this->m_warnings);
    memcpy(&this->m_numUnservedDriveThroughPens, &buffer[offset], sizeof(this->m_numUnservedDriveThroughPens));
    offset += sizeof(this->m_numUnservedDriveThroughPens);
    memcpy(&this->m_numUnservedStopGoPens, &buffer[offset], sizeof(this->m_numUnservedStopGoPens));
    offset += sizeof(this->m_numUnservedStopGoPens);
    memcpy(&this->m_gridPosition, &buffer[offset], sizeof(this->m_gridPosition));
    offset += sizeof(this->m_gridPosition);
    memcpy(&this->m_driverStatus, &buffer[offset], sizeof(this->m_driverStatus));
    offset += sizeof(this->m_driverStatus);
    memcpy(&this->m_resultStatus, &buffer[offset], sizeof(this->m_resultStatus));
    offset += sizeof(this->m_resultStatus);
    memcpy(&this->m_pitLaneTimerActive, &buffer[offset], sizeof(this->m_pitLaneTimerActive));
    offset += sizeof(this->m_pitLaneTimerActive);
    memcpy(&this->m_pitLaneTimeInLaneInMS, &buffer[offset], sizeof(this->m_pitLaneTimeInLaneInMS));
    offset += sizeof(this->m_pitLaneTimeInLaneInMS);
    memcpy(&this->m_pitStopTimerInMS, &buffer[offset], sizeof(this->m_pitStopTimerInMS));
    offset += sizeof(this->m_pitStopTimerInMS);
    memcpy(&this->m_pitStopShouldServePen, &buffer[offset], sizeof(this->m_pitStopShouldServePen));
    offset += sizeof(this->m_pitStopShouldServePen);
    
    return offset;
  }
};

struct PacketLapData {
  PacketHeader m_header; // Header
  LapData m_lapData[22]; // Lap data for all cars on track
  uint8_t m_timeTrialPBCarIdx; // Index of Personal Best car in time trial (255 if invalid)
  uint8_t m_timeTrialRivalCarIdx; // Index of Rival car in time trial (255 if invalid)

  void get(char* buffer){
    unsigned long offset = this->m_header.get(buffer);
    for (int i = 0; i < 22; i++){
        offset = this->m_lapData[i].get(buffer,offset);
    }
    memcpy(&this->m_timeTrialPBCarIdx, &buffer[offset], sizeof(this->m_timeTrialPBCarIdx));
    offset += sizeof(this->m_timeTrialPBCarIdx);
    memcpy(&this->m_timeTrialRivalCarIdx, &buffer[offset], sizeof(this->m_timeTrialRivalCarIdx));
    offset += sizeof(this->m_timeTrialRivalCarIdx);
  }
};

union EventDataDetails {
  struct {
    uint8_t vehicleIdx; // Vehicle index of car achieving fastest lap
    float lapTime; // Lap time is in seconds

    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->vehicleIdx, &buffer[offset], sizeof(this->vehicleIdx));
      offset = offset + sizeof(this->vehicleIdx);
      memcpy(&this->lapTime, &buffer[offset], sizeof(this->lapTime));
      offset = offset + sizeof(this->lapTime);
      return offset;
    }
  } FastestLap;
  struct {
    uint8_t vehicleIdx; // Vehicle index of car retiring

    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->vehicleIdx, &buffer[offset], sizeof(this->vehicleIdx));
      offset = offset + sizeof(this->vehicleIdx);
      return offset;
    }
  } Retirement;
  struct {
    uint8_t vehicleIdx; // Vehicle index of team mate

    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->vehicleIdx, &buffer[offset], sizeof(this->vehicleIdx));
      offset = offset + sizeof(this->vehicleIdx);
      return offset;
    }
  } TeamMateInPits;
  struct {
    uint8_t vehicleIdx; // Vehicle index of the race winner

    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->vehicleIdx, &buffer[offset], sizeof(this->vehicleIdx));
      offset = offset + sizeof(this->vehicleIdx);
      return offset;
    }    
  } RaceWinner;
  struct {
    uint8_t penaltyType; // Penalty type – see Appendices
    uint8_t infringementType; // Infringement type – see Appendices
    uint8_t vehicleIdx; // Vehicle index of the car the penalty is applied to
    uint8_t otherVehicleIdx; // Vehicle index of the other car involved
    uint8_t time; // Time gained, or time spent doing action in seconds
    uint8_t lapNum; // Lap the penalty occurred on
    uint8_t placesGained; // Number of places gained by this

    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->penaltyType, &buffer[offset], sizeof(this->penaltyType));
      offset += sizeof(this->penaltyType);
      memcpy(&this->infringementType, &buffer[offset], sizeof(this->infringementType));
      offset += sizeof(this->infringementType);
      memcpy(&this->vehicleIdx, &buffer[offset], sizeof(this->vehicleIdx));
      offset += sizeof(this->vehicleIdx);
      memcpy(&this->otherVehicleIdx, &buffer[offset], sizeof(this->otherVehicleIdx));
      offset += sizeof(this->otherVehicleIdx);
      memcpy(&this->time, &buffer[offset], sizeof(this->time));
      offset += sizeof(this->time);
      memcpy(&this->lapNum, &buffer[offset], sizeof(this->lapNum));
      offset += sizeof(this->lapNum);
      memcpy(&this->placesGained, &buffer[offset], sizeof(this->placesGained));
      offset += sizeof(this->placesGained);
      return offset;
    }
  } Penalty;
  struct {
    uint8_t vehicleIdx; // Vehicle index of the vehicle triggering speed trap
    float speed; // Top speed achieved in kilometres per hour
    uint8_t isOverallFastestInSession; // Overall fastest speed in session = 1, otherwise 0
    uint8_t isDriverFastestInSession; // Fastest speed for driver in session = 1, otherwise 0
    uint8_t fastestVehicleIdxInSession;// Vehicle index of the vehicle that is the fastest
    // in this session
    float fastestSpeedInSession; // Speed of the vehicle that is the fastest
    // in this session

    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->vehicleIdx, &buffer[offset], sizeof(this->vehicleIdx));
      offset = offset + sizeof(this->vehicleIdx);
      memcpy(&this->speed, &buffer[offset], sizeof(this->speed));
      offset = offset + sizeof(this->speed);
      memcpy(&this->isOverallFastestInSession, &buffer[offset], sizeof(this->isOverallFastestInSession));
      offset = offset + sizeof(this->isOverallFastestInSession);
      memcpy(&this->isDriverFastestInSession, &buffer[offset], sizeof(this->isDriverFastestInSession));
      offset = offset + sizeof(this->isDriverFastestInSession);
      memcpy(&this->fastestVehicleIdxInSession, &buffer[offset], sizeof(this->fastestVehicleIdxInSession));
      offset = offset + sizeof(this->fastestVehicleIdxInSession);
      memcpy(&this->fastestSpeedInSession, &buffer[offset], sizeof(this->fastestSpeedInSession));
      offset = offset + sizeof(this->fastestSpeedInSession);
      return offset;
    }
  } SpeedTrap;
  struct {
    uint8_t numLights; // Number of lights showing

    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->numLights, &buffer[offset], sizeof(this->numLights));
      offset = offset + sizeof(this->numLights);
      return offset;
    }
  } StartLights;
  struct {
    uint8_t vehicleIdx; // Vehicle index of the vehicle serving drive through
      unsigned long get(char* buffer, unsigned long offset) {
        memcpy(&this->vehicleIdx, &buffer[offset], sizeof(this->vehicleIdx));
        offset = offset + sizeof(this->vehicleIdx);
        return offset;
      }
  } DriveThroughPenaltyServed;
  struct {
    uint8_t vehicleIdx; // Vehicle index of the vehicle serving stop go
    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->vehicleIdx, &buffer[offset], sizeof(this->vehicleIdx));
      offset = offset + sizeof(this->vehicleIdx);
      return offset;
    }
  } StopGoPenaltyServed;
  struct {
    uint32_t flashbackFrameIdentifier; // Frame identifier flashed back to
    float flashbackSessionTime; // Session time flashed back to
    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->flashbackFrameIdentifier, &buffer[offset], sizeof(this->flashbackFrameIdentifier));
      offset = offset + sizeof(this->flashbackFrameIdentifier);
      memcpy(&this->flashbackSessionTime, &buffer[offset], sizeof(this->flashbackSessionTime));
      offset = offset + sizeof(this->flashbackSessionTime);
      return offset;
    }
  } Flashback;
  struct {
    uint32_t m_buttonStatus; // Bit flags specifying which buttons are being pressed
    // currently - see appendices
    unsigned long get(char* buffer, unsigned long offset) {
      memcpy(&this->m_buttonStatus, &buffer[offset], sizeof(this->m_buttonStatus));
      offset = offset + sizeof(this->m_buttonStatus);
      return offset;
    }
  } Buttons;
};

struct PacketEventData {
  PacketHeader m_header; // Header
  uint8_t m_eventStringCode[4]; // Event string code, see below
  EventDataDetails m_eventDetails; // Event details - should be interpreted differently
  // for each type
  void get(char* buffer) {
    unsigned long offset = this->m_header.get(buffer);
    memcpy(&this->m_eventStringCode, &buffer[offset], sizeof(m_eventStringCode));
    offset = offset + sizeof(m_eventStringCode);
    if(!strcmp((const char*)this->m_eventStringCode, "SSTA")){
    }else if(!strcmp((const char*)this->m_eventStringCode, "SEND")){
    }else if(!strcmp((const char*)this->m_eventStringCode, "FTLP")){
      this->m_eventDetails.FastestLap.get(buffer, offset);
    }else if(!strcmp((const char*)this->m_eventStringCode, "RTML")){
      this->m_eventDetails.Retirement.get(buffer, offset);
    }else if(!strcmp((const char*)this->m_eventStringCode, "DRSE")){
    }else if(!strcmp((const char*)this->m_eventStringCode, "DRSD")){
    }else if(!strcmp((const char*)this->m_eventStringCode, "TMPT")){
      this->m_eventDetails.TeamMateInPits.get(buffer, offset);
    }else if(!strcmp((const char*)this->m_eventStringCode, "CHQF")){
    }else if(!strcmp((const char*)this->m_eventStringCode, "RCWN")){
      this->m_eventDetails.RaceWinner.get(buffer, offset);
    }else if(!strcmp((const char*)this->m_eventStringCode, "PENA")){
      this->m_eventDetails.Penalty.get(buffer, offset);
    }else if(!strcmp((const char*)this->m_eventStringCode, "SPTP")){
    }else if(!strcmp((const char*)this->m_eventStringCode, "STLG")){
      this->m_eventDetails.StartLights.get(buffer, offset);
    }else if(!strcmp((const char*)this->m_eventStringCode, "LGOT")){
    }else if(!strcmp((const char*)this->m_eventStringCode, "DTSV")){
      this->m_eventDetails.DriveThroughPenaltyServed.get(buffer, offset);
    }else if(!strcmp((const char*)this->m_eventStringCode, "SGSV")){
      this->m_eventDetails.StopGoPenaltyServed.get(buffer, offset);
    }else if(!strcmp((const char*)this->m_eventStringCode, "FLBK")){
      this->m_eventDetails.Flashback.get(buffer, offset);
    }else if(!strcmp((const char*)this->m_eventStringCode, "BUTN")){
      this->m_eventDetails.Buttons.get(buffer, offset);
    }
  }
};

struct ParticipantData {
  uint8_t m_aiControlled; // Whether the vehicle is AI (1) or Human (0) controlled
  uint8_t m_driverId; // Driver id - see appendix, 255 if network human
  uint8_t m_networkId; // Network id – unique identifier for network players
  uint8_t m_teamId; // Team id - see appendix
  uint8_t m_myTeam; // My team flag – 1 = My Team, 0 = otherwise
  uint8_t m_raceNumber; // Race number of the car
  uint8_t m_nationality; // Nationality of the driver
  char m_name[48]; // Name of participant in UTF-8 format – null terminated
  // Will be truncated with ... (U+2026) if too long
  uint8_t m_yourTelemetry; // The player's UDP setting, 0 = restricted, 1 = public

  unsigned long get(char* buffer,unsigned long offset){
    memcpy(&this->m_aiControlled,&buffer[offset],sizeof(this->m_aiControlled));
    offset += sizeof(this->m_aiControlled);
    memcpy(&this->m_driverId,&buffer[offset],sizeof(this->m_driverId));
    offset += sizeof(this->m_driverId);
    memcpy(&this->m_networkId,&buffer[offset],sizeof(this->m_networkId));
    offset += sizeof(this->m_networkId);
    memcpy(&this->m_teamId,&buffer[offset],sizeof(this->m_teamId));
    offset += sizeof(this->m_teamId);
    memcpy(&this->m_raceNumber,&buffer[offset],sizeof(this->m_raceNumber));
    offset += sizeof(this->m_raceNumber);
    memcpy(&this->m_nationality,&buffer[offset],sizeof(this->m_nationality));
    offset += sizeof(this->m_nationality);
    memcpy(&this->m_name,&buffer[offset],sizeof(this->m_name));
    offset += 48UL;
    memcpy(&this->m_yourTelemetry,&buffer[offset],sizeof(this->m_yourTelemetry));
    offset += sizeof(this->m_yourTelemetry);
    return offset;
  }
};

struct PacketParticipantsData {
  PacketHeader m_header; // Header
  uint8_t m_numActiveCars; // Number of active cars in the data – should match number of
  // cars on HUD
  ParticipantData m_participants[22];

  void get(char* buffer){
    unsigned long offset = this->m_header.get(buffer);
    memcpy(&this->m_numActiveCars,&buffer[offset],sizeof(this->m_numActiveCars));
    offset += sizeof(this->m_numActiveCars);
    for (int i = 0; i < this->m_numActiveCars; i++){
        offset = this->m_participants[i].get(buffer,offset);
    }
  } 
};

struct CarSetupData {
  uint8_t m_frontWing; // Front wing aero
  uint8_t m_rearWing; // Rear wing aero
  uint8_t m_onThrottle; // Differential adjustment on throttle (percentage)
  uint8_t m_offThrottle; // Differential adjustment off throttle (percentage)
  float m_frontCamber; // Front camber angle (suspension geometry)
  float m_rearCamber; // Rear camber angle (suspension geometry)
  float m_frontToe; // Front toe angle (suspension geometry)
  float m_rearToe; // Rear toe angle (suspension geometry)
  uint8_t m_frontSuspension; // Front suspension
  uint8_t m_rearSuspension; // Rear suspension
  uint8_t m_frontAntiRollBar; // Front anti-roll bar
  uint8_t m_rearAntiRollBar; // Front anti-roll bar
  uint8_t m_frontSuspensionHeight; // Front ride height
  uint8_t m_rearSuspensionHeight; // Rear ride height
  uint8_t m_brakePressure; // Brake pressure (percentage)
  uint8_t m_brakeBias; // Brake bias (percentage)
  float m_rearLeftTyrePressure; // Rear left tyre pressure (PSI)
  float m_rearRightTyrePressure; // Rear right tyre pressure (PSI)
  float m_frontLeftTyrePressure; // Front left tyre pressure (PSI)
  float m_frontRightTyrePressure; // Front right tyre pressure (PSI)
  uint8_t m_ballast; // Ballast
  float m_fuelLoad; // Fuel load

  unsigned long get(char* buffer,unsigned long offset){
    memcpy(&this->m_frontWing,&buffer[offset],sizeof(this->m_frontWing));
    offset = offset + sizeof(this->m_frontWing);
    memcpy(&this->m_rearWing,&buffer[offset],sizeof(this->m_rearWing));
    offset = offset + sizeof(this->m_rearWing);
    memcpy(&this->m_onThrottle,&buffer[offset],sizeof(this->m_onThrottle));
    offset = offset + sizeof(this->m_onThrottle);
    memcpy(&this->m_offThrottle,&buffer[offset],sizeof(this->m_offThrottle));
    offset = offset + sizeof(this->m_offThrottle);
    memcpy(&this->m_frontCamber,&buffer[offset],sizeof(this->m_frontCamber));
    offset = offset + sizeof(this->m_frontCamber);
    memcpy(&this->m_rearCamber,&buffer[offset],sizeof(this->m_rearCamber));
    offset = offset + sizeof(this->m_rearCamber);
    memcpy(&this->m_frontToe,&buffer[offset],sizeof(this->m_frontToe));
    offset = offset + sizeof(this->m_frontToe);
    memcpy(&this->m_rearToe,&buffer[offset],sizeof(this->m_rearToe));
    offset = offset + sizeof(this->m_rearToe);
    memcpy(&this->m_frontSuspension,&buffer[offset],sizeof(this->m_frontSuspension));
    offset = offset + sizeof(this->m_frontSuspension);
    memcpy(&this->m_rearSuspension,&buffer[offset],sizeof(this->m_rearSuspension));
    offset = offset + sizeof(this->m_rearSuspension);
    memcpy(&this->m_frontAntiRollBar,&buffer[offset],sizeof(this->m_frontAntiRollBar));
    offset = offset + sizeof(this->m_frontAntiRollBar);
    memcpy(&this->m_rearAntiRollBar,&buffer[offset],sizeof(this->m_rearAntiRollBar));
    offset = offset + sizeof(this->m_rearAntiRollBar);
    memcpy(&this->m_frontSuspensionHeight,&buffer[offset],sizeof(this->m_frontSuspensionHeight));
    offset = offset + sizeof(this->m_frontSuspensionHeight);
    memcpy(&this->m_rearSuspensionHeight,&buffer[offset],sizeof(this->m_rearSuspensionHeight));
    offset = offset + sizeof(this->m_rearSuspensionHeight);
    memcpy(&this->m_brakePressure,&buffer[offset],sizeof(this->m_brakePressure));
    offset = offset + sizeof(this->m_brakePressure);
    memcpy(&this->m_brakeBias,&buffer[offset],sizeof(this->m_brakeBias));
    offset = offset + sizeof(this->m_brakeBias);
    memcpy(&this->m_rearLeftTyrePressure,&buffer[offset],sizeof(this->m_rearLeftTyrePressure));
    offset = offset + sizeof(this->m_rearLeftTyrePressure);
    memcpy(&this->m_rearRightTyrePressure,&buffer[offset],sizeof(this->m_rearRightTyrePressure));
    offset = offset + sizeof(this->m_rearRightTyrePressure);
    memcpy(&this->m_frontLeftTyrePressure,&buffer[offset],sizeof(this->m_frontLeftTyrePressure));
    offset = offset + sizeof(this->m_frontLeftTyrePressure);
    memcpy(&this->m_frontRightTyrePressure,&buffer[offset],sizeof(this->m_frontRightTyrePressure));
    offset = offset + sizeof(this->m_frontRightTyrePressure);
    memcpy(&this->m_ballast,&buffer[offset],sizeof(this->m_ballast));
    offset = offset + sizeof(this->m_ballast);
    memcpy(&this->m_fuelLoad,&buffer[offset],sizeof(this->m_fuelLoad));
    offset = offset + sizeof(this->m_fuelLoad);
    return offset;
  }  
};

struct PacketCarSetupData {
  PacketHeader m_header; // Header
  CarSetupData m_carSetups[22];

  void get(char* buffer){
    unsigned long offset = this->m_header.get(buffer);
    for (int i = 0; i < 22; i++){
        offset = this->m_carSetups[i].get(buffer,offset);
    }
  }
};

struct CarTelemetryData {
  uint16_t m_speed; // Speed of car in kilometres per hour
  float m_throttle; // Amount of throttle applied (0.0 to 1.0)
  float m_steer; // Steering (-1.0 (full lock left) to 1.0 (full lock right))
  float m_brake; // Amount of brake applied (0.0 to 1.0)
  uint8_t m_clutch; // Amount of clutch applied (0 to 100)
  int8_t m_gear; // Gear selected (1-8, N=0, R=-1)
  uint16_t m_engineRPM; // Engine RPM
  uint8_t m_drs; // 0 = off, 1 = on
  uint8_t m_revLightsPercent; // Rev lights indicator (percentage)
  uint16_t m_revLightsBitValue; // Rev lights (bit 0 = leftmost LED, bit 14 = rightmost LED)
  uint16_t m_brakesTemperature[4]; // Brakes temperature (celsius)
  uint8_t m_tyresSurfaceTemperature[4]; // Tyres surface temperature (celsius)
  uint8_t m_tyresInnerTemperature[4]; // Tyres inner temperature (celsius)
  uint16_t m_engineTemperature; // Engine temperature (celsius)
  float m_tyresPressure[4]; // Tyres pressure (PSI)
  uint8_t m_surfaceType[4]; // Driving surface, see appendices

  unsigned long get(char *buffer, unsigned long offset) {
    memcpy(&this->m_speed, &buffer[offset], sizeof(this->m_speed));
    offset = offset + sizeof(this->m_speed);
    memcpy(&this->m_throttle, &buffer[offset], sizeof(this->m_throttle));
    offset = offset + sizeof(this->m_throttle);
    memcpy(&this->m_steer, &buffer[offset], sizeof(this->m_steer));
    offset = offset + sizeof(this->m_steer);
    memcpy(&this->m_brake, &buffer[offset], sizeof(this->m_brake));
    offset = offset + sizeof(this->m_brake);
    memcpy(&this->m_clutch, &buffer[offset], sizeof(this->m_clutch));
    offset = offset + sizeof(this->m_clutch);
    memcpy(&this->m_gear, &buffer[offset], sizeof(this->m_gear));
    offset = offset + sizeof(this->m_gear);
    memcpy(&this->m_engineRPM, &buffer[offset], sizeof(this->m_engineRPM));
    offset = offset + sizeof(this->m_engineRPM);
    memcpy(&this->m_drs, &buffer[offset], sizeof(this->m_drs));
    offset = offset + sizeof(this->m_drs);
    memcpy(&this->m_revLightsPercent, &buffer[offset], sizeof(this->m_revLightsPercent));
    offset = offset + sizeof(this->m_revLightsPercent);
    memcpy(&this->m_revLightsBitValue, &buffer[offset], sizeof(this->m_revLightsBitValue));
    offset = offset + sizeof(this->m_revLightsBitValue);
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_brakesTemperature[i], &buffer[offset], sizeof(this->m_brakesTemperature[i]));
      offset = offset + sizeof(this->m_brakesTemperature[i]);
    }
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_tyresSurfaceTemperature[i], &buffer[offset], sizeof(this->m_tyresSurfaceTemperature[i]));
      offset = offset + sizeof(this->m_tyresSurfaceTemperature[i]);
    }
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_tyresInnerTemperature[i], &buffer[offset], sizeof(this->m_tyresInnerTemperature[i]));
      offset = offset + sizeof(this->m_tyresInnerTemperature[i]);
    }
    memcpy(&this->m_engineTemperature, &buffer[offset], sizeof(this->m_engineTemperature));
    offset = offset + sizeof(this->m_engineTemperature);
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_tyresPressure[i], &buffer[offset], sizeof(this->m_tyresPressure[i]));
      offset = offset + sizeof(this->m_tyresPressure[i]);
    }
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_surfaceType[i], &buffer[offset], sizeof(this->m_surfaceType[i]));
      offset = offset + sizeof(this->m_surfaceType[i]);
    }
    return offset;
  }
};

struct PacketCarTelemetryData {
  PacketHeader m_header; // Header
  CarTelemetryData m_carTelemetryData[22];
  uint8_t m_mfdPanelIndex; // Index of MFD panel open - 255 = MFD closed
  // Single player, race – 0 = Car setup, 1 = Pits
  // 2 = Damage, 3 = Engine, 4 = Temperatures
  // May vary depending on game mode
  uint8_t m_mfdPanelIndexSecondaryPlayer; // See above
  int8_t m_suggestedGear; // Suggested gear for the player (1-8)
  // 0 if no gear suggested

  void get(char *buffer) {
    unsigned long offset = this->m_header.get(buffer);
    for (int i = 0; i < 22; i++) {
      offset = this->m_carTelemetryData[i].get(buffer, offset);
    }
    memcpy(&this->m_mfdPanelIndex, &buffer[offset], sizeof(this->m_mfdPanelIndex));
    offset = offset + sizeof(this->m_mfdPanelIndex);
    memcpy(&this->m_mfdPanelIndexSecondaryPlayer, &buffer[offset], sizeof(this->m_mfdPanelIndexSecondaryPlayer));
    offset = offset + sizeof(this->m_mfdPanelIndexSecondaryPlayer);
    memcpy(&this->m_suggestedGear, &buffer[offset], sizeof(this->m_suggestedGear));
    offset = offset + sizeof(this->m_suggestedGear);
  }
};

struct CarStatusData {
  uint8_t m_tractionControl; // Traction control - 0 = off, 1 = medium, 2 = full
  uint8_t m_antiLockBrakes; // 0 (off) - 1 (on)
  uint8_t m_fuelMix; // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
  uint8_t m_frontBrakeBias; // Front brake bias (percentage)
  uint8_t m_pitLimiterStatus; // Pit limiter status - 0 = off, 1 = on
  float m_fuelInTank; // Current fuel mass
  float m_fuelCapacity; // Fuel capacity
  float m_fuelRemainingLaps; // Fuel remaining in terms of laps (value on MFD)
  uint16_t m_maxRPM; // Cars max RPM, point of rev limiter
  uint16_t m_idleRPM; // Cars idle RPM
  uint8_t m_maxGears; // Maximum number of gears
  uint8_t m_drsAllowed; // 0 = not allowed, 1 = allowed
  uint16_t m_drsActivationDistance; // 0 = DRS not available, non-zero - DRS will be available
  // in [X] metres
  uint8_t m_actualTyreCompound; // F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
  // 7 = inter, 8 = wet
  // F1 Classic - 9 = dry, 10 = wet
  // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
  // 15 = wet
  uint8_t m_visualTyreCompound; // F1 visual (can be different from actual compound)
  // 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
  // F1 Classic – same as above
  // F2 ‘19, 15 = wet, 19 – super soft, 20 = soft
  // 21 = medium , 22 = hard
  uint8_t m_tyresAgeLaps; // Age in laps of the current set of tyres
  int8_t m_vehicleFiaFlags; // -1 = invalid/unknown, 0 = none, 1 = green
  // 2 = blue, 3 = yellow, 4 = red
  float m_ersStoreEnergy; // ERS energy store in Joules
  uint8_t m_ersDeployMode; // ERS deployment mode, 0 = none, 1 = medium
  // 2 = hotlap, 3 = overtake
  float m_ersHarvestedThisLapMGUK; // ERS energy harvested this lap by MGU-K
  float m_ersHarvestedThisLapMGUH; // ERS energy harvested this lap by MGU-H
  float m_ersDeployedThisLap; // ERS energy deployed this lap
  uint8_t m_networkPaused; // Whether the car is paused in a network game

  unsigned long get(char* buffer, unsigned long offset) {
    memcpy(&this->m_tractionControl, &buffer[offset], sizeof(this->m_tractionControl));
    offset = offset + sizeof(this->m_tractionControl);
    memcpy(&this->m_antiLockBrakes, &buffer[offset], sizeof(this->m_antiLockBrakes));
    offset = offset + sizeof(this->m_antiLockBrakes);
    memcpy(&this->m_fuelMix, &buffer[offset], sizeof(this->m_fuelMix));
    offset = offset + sizeof(this->m_fuelMix);
    memcpy(&this->m_frontBrakeBias, &buffer[offset], sizeof(this->m_frontBrakeBias));
    offset = offset + sizeof(this->m_frontBrakeBias);
    memcpy(&this->m_pitLimiterStatus, &buffer[offset], sizeof(this->m_pitLimiterStatus));
    offset = offset + sizeof(this->m_pitLimiterStatus);
    memcpy(&this->m_fuelInTank, &buffer[offset], sizeof(this->m_fuelInTank));
    offset = offset + sizeof(this->m_fuelInTank);
    memcpy(&this->m_fuelCapacity, &buffer[offset], sizeof(this->m_fuelCapacity));
    offset = offset + sizeof(this->m_fuelCapacity);
    memcpy(&this->m_fuelRemainingLaps, &buffer[offset], sizeof(this->m_fuelRemainingLaps));
    offset = offset + sizeof(this->m_fuelRemainingLaps);
    memcpy(&this->m_maxRPM, &buffer[offset], sizeof(this->m_maxRPM));
    offset = offset + sizeof(this->m_maxRPM);
    memcpy(&this->m_idleRPM, &buffer[offset], sizeof(this->m_idleRPM));
    offset = offset + sizeof(this->m_idleRPM);
    memcpy(&this->m_maxGears, &buffer[offset], sizeof(this->m_maxGears));
    offset = offset + sizeof(this->m_maxGears);
    memcpy(&this->m_drsAllowed, &buffer[offset], sizeof(this->m_drsAllowed));
    offset = offset + sizeof(this->m_drsAllowed);
    memcpy(&this->m_drsActivationDistance, &buffer[offset], sizeof(this->m_drsActivationDistance));
    offset = offset + sizeof(this->m_drsActivationDistance);
    memcpy(&this->m_actualTyreCompound, &buffer[offset], sizeof(this->m_actualTyreCompound));
    offset = offset + sizeof(this->m_actualTyreCompound);
    memcpy(&this->m_visualTyreCompound, &buffer[offset], sizeof(this->m_visualTyreCompound));
    offset = offset + sizeof(this->m_visualTyreCompound);
    memcpy(&this->m_tyresAgeLaps, &buffer[offset], sizeof(this->m_tyresAgeLaps));
    offset = offset + sizeof(this->m_tyresAgeLaps);
    memcpy(&this->m_vehicleFiaFlags, &buffer[offset], sizeof(this->m_vehicleFiaFlags));
    offset = offset + sizeof(this->m_vehicleFiaFlags);
    memcpy(&this->m_ersStoreEnergy, &buffer[offset], sizeof(this->m_ersStoreEnergy));
    offset = offset + sizeof(this->m_ersStoreEnergy);
    memcpy(&this->m_ersDeployMode, &buffer[offset], sizeof(this->m_ersDeployMode));
    offset = offset + sizeof(this->m_ersDeployMode);
    memcpy(&this->m_ersHarvestedThisLapMGUK, &buffer[offset], sizeof(this->m_ersHarvestedThisLapMGUK));
    offset = offset + sizeof(this->m_ersHarvestedThisLapMGUK);
    memcpy(&this->m_ersHarvestedThisLapMGUH, &buffer[offset], sizeof(this->m_ersHarvestedThisLapMGUH));
    offset = offset + sizeof(this->m_ersHarvestedThisLapMGUH);
    memcpy(&this->m_ersDeployedThisLap, &buffer[offset], sizeof(this->m_ersDeployedThisLap));
    offset = offset + sizeof(this->m_ersDeployedThisLap);
    memcpy(&this->m_networkPaused, &buffer[offset], sizeof(this->m_networkPaused));
    offset = offset + sizeof(this->m_networkPaused);
    return offset;
  }
};

struct PacketCarStatusData {
  PacketHeader m_header; // Header
  CarStatusData m_carStatusData[22];

  void get(char* buffer) {
    unsigned long offset = this->m_header.get(buffer);
    for (int i = 0; i < 22; i++) {
      offset = m_carStatusData[i].get(buffer, offset);
    }
  }
};

struct FinalClassificationData {
  uint8_t m_position; // Finishing position
  uint8_t m_numLaps; // Number of laps completed
  uint8_t m_gridPosition; // Grid position of the car
  uint8_t m_points; // Number of points scored
  uint8_t m_numPitStops; // Number of pit stops made
  uint8_t m_resultStatus; // Result status - 0 = invalid, 1 = inactive, 2 = active
  // 3 = finished, 4 = didnotfinish, 5 = disqualified
  // 6 = not classified, 7 = retired
  uint32_t m_bestLapTimeInMS; // Best lap time of the session in milliseconds
  double m_totalRaceTime; // Total race time in seconds without penalties
  uint8_t m_penaltiesTime; // Total penalties accumulated in seconds
  uint8_t m_numPenalties; // Number of penalties applied to this driver
  uint8_t m_numTyreStints; // Number of tyres stints up to maximum
  uint8_t m_tyreStintsActual[8]; // Actual tyres used by this driver
  uint8_t m_tyreStintsVisual[8]; // Visual tyres used by this driver
  uint8_t m_tyreStintsEndLaps[8]; // The lap number stints end on

  unsigned long get(char * buffer,unsigned long offset){
    memcpy(&this->m_position,&buffer[offset],sizeof(this->m_position));
    offset = offset + sizeof(this->m_position);
    memcpy(&this->m_numLaps,&buffer[offset],sizeof(this->m_numLaps));
    offset = offset + sizeof(this->m_numLaps);
    memcpy(&this->m_gridPosition,&buffer[offset],sizeof(this->m_gridPosition));
    offset = offset + sizeof(this->m_gridPosition);
    memcpy(&this->m_points,&buffer[offset],sizeof(this->m_points));
    offset = offset + sizeof(this->m_points);
    memcpy(&this->m_numPitStops,&buffer[offset],sizeof(this->m_numPitStops));
    offset = offset + sizeof(this->m_numPitStops);
    memcpy(&this->m_resultStatus,&buffer[offset],sizeof(this->m_resultStatus));
    offset = offset + sizeof(this->m_resultStatus);
    memcpy(&this->m_bestLapTimeInMS,&buffer[offset],sizeof(this->m_bestLapTimeInMS));
    offset = offset + sizeof(this->m_bestLapTimeInMS);
    memcpy(&this->m_totalRaceTime,&buffer[offset],sizeof(this->m_totalRaceTime));
    offset = offset + sizeof(this->m_totalRaceTime);
    memcpy(&this->m_penaltiesTime,&buffer[offset],sizeof(this->m_penaltiesTime));
    offset = offset + sizeof(this->m_penaltiesTime);
    memcpy(&this->m_numPenalties,&buffer[offset],sizeof(this->m_numPenalties));
    offset = offset + sizeof(this->m_numPenalties);
    memcpy(&this->m_numTyreStints,&buffer[offset],sizeof(this->m_numTyreStints));
    offset = offset + sizeof(this->m_numTyreStints);
    for (int i = 0; i < 8; i++) {
      memcpy(&this->m_tyreStintsActual[i],&buffer[offset],sizeof(this->m_tyreStintsActual[i]));
      offset = offset + sizeof(this->m_tyreStintsActual[i]);
    }
    for (int i = 0; i < 8; i++) {
      memcpy(&this->m_tyreStintsVisual[i],&buffer[offset],sizeof(this->m_tyreStintsVisual[i]));
      offset = offset + sizeof(this->m_tyreStintsVisual[i]);
    }
    for (int i = 0; i < 8; i++) {
      memcpy(&this->m_tyreStintsEndLaps[i],&buffer[offset],sizeof(this->m_tyreStintsEndLaps[i]));
      offset = offset + sizeof(this->m_tyreStintsEndLaps[i]);
    }

    return offset;
  }
};

struct PacketFinalClassificationData {
  PacketHeader m_header; // Header
  uint8_t m_numCars; // Number of cars in the final classification
  FinalClassificationData m_classificationData[22];

  void get(char * buffer){
    unsigned long offset = this->m_header.get(buffer);
    memcpy(&this->m_numCars,&buffer[offset],sizeof(this->m_numCars));
    offset = offset + sizeof(this->m_numCars);
    for (int i = 0; i < 22; i++) {
      offset = this->m_classificationData[i].get(buffer,offset);
    }
  }
};

struct LobbyInfoData {
  uint8_t m_aiControlled; // Whether the vehicle is AI (1) or Human (0) controlled
  uint8_t m_teamId; // Team id - see appendix (255 if no team currently selected)
  uint8_t m_nationality; // Nationality of the driver
  char m_name[48]; // Name of participant in UTF-8 format – null terminated
  // Will be truncated with ... (U+2026) if too long
  uint8_t m_carNumber; // Car number of the player
  uint8_t m_readyStatus; // 0 = not ready, 1 = ready, 2 = spectating

  unsigned long get(char * buffer,unsigned long offset){
    memcpy(&this->m_aiControlled,&buffer[offset],sizeof(this->m_aiControlled));
    offset = offset + sizeof(this->m_aiControlled);
    memcpy(&this->m_teamId,&buffer[offset],sizeof(this->m_teamId));
    offset = offset + sizeof(this->m_teamId);
    memcpy(&this->m_nationality,&buffer[offset],sizeof(this->m_nationality));
    offset = offset + sizeof(this->m_nationality);
    for (int i = 0; i < 48; i++){
      memcpy(&this->m_name,&buffer[offset],sizeof(this->m_name));
      offset = offset + sizeof(this->m_name);
    }
    memcpy(&this->m_carNumber,&buffer[offset],sizeof(this->m_carNumber));
    offset = offset + sizeof(this->m_carNumber);
    memcpy(&this->m_readyStatus,&buffer[offset],sizeof(this->m_readyStatus));
    offset = offset + sizeof(this->m_readyStatus);
    return offset;
  }
};

struct PacketLobbyInfoData {
  PacketHeader m_header; // Header
  // Packet specific data
  uint8_t m_numPlayers; // Number of players in the lobby data
  LobbyInfoData m_lobbyPlayers[22];

  void get(char * buffer){
    unsigned long offset = this->m_header.get(buffer);
    memcpy(&this->m_numPlayers,&buffer[offset],sizeof(this->m_numPlayers));
    offset = offset + sizeof(this->m_numPlayers);
    for (int i = 0; i < this->m_numPlayers; i++){
      offset = this->m_lobbyPlayers[i].get(buffer,offset);
    }
  }
};

struct CarDamageData {
  float m_tyresWear[4]; // Tyre wear (percentage)
  uint8_t m_tyresDamage[4]; // Tyre damage (percentage)
  uint8_t m_brakesDamage[4]; // Brakes damage (percentage)
  uint8_t m_frontLeftWingDamage; // Front left wing damage (percentage)
  uint8_t m_frontRightWingDamage; // Front right wing damage (percentage)
  uint8_t m_rearWingDamage; // Rear wing damage (percentage)
  uint8_t m_floorDamage; // Floor damage (percentage)
  uint8_t m_diffuserDamage; // Diffuser damage (percentage)
  uint8_t m_sidepodDamage; // Sidepod damage (percentage)
  uint8_t m_drsFault; // Indicator for DRS fault, 0 = OK, 1 = fault
  uint8_t m_ersFault; // Indicator for ERS fault, 0 = OK, 1 = fault
  uint8_t m_gearBoxDamage; // Gear box damage (percentage)
  uint8_t m_engineDamage; // Engine damage (percentage)
  uint8_t m_engineMGUHWear; // Engine wear MGU-H (percentage)
  uint8_t m_engineESWear; // Engine wear ES (percentage)
  uint8_t m_engineCEWear; // Engine wear CE (percentage)
  uint8_t m_engineICEWear; // Engine wear ICE (percentage)
  uint8_t m_engineMGUKWear; // Engine wear MGU-K (percentage)
  uint8_t m_engineTCWear; // Engine wear TC (percentage)
  uint8_t m_engineBlown; // Engine blown, 0 = OK, 1 = fault
  uint8_t m_engineSeized; // Engine seized, 0 = OK, 1 = fault

  unsigned long get(char* buffer, unsigned long offset) {
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_tyresWear[i], &buffer[offset], sizeof(this->m_tyresWear[i]));
      offset = offset + sizeof(this->m_tyresWear[i]);
    }
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_tyresDamage[i], &buffer[offset], sizeof(this->m_tyresDamage[i]));
      offset = offset + sizeof(this->m_tyresDamage[i]);
    }
    for (int i = 0; i < 4; i++) {
      memcpy(&this->m_brakesDamage[i], &buffer[offset], sizeof(this->m_brakesDamage[i]));
      offset = offset + sizeof(this->m_brakesDamage[i]);
    }
    memcpy(&this->m_frontLeftWingDamage, &buffer[offset], sizeof(this->m_frontLeftWingDamage));
    offset = offset + sizeof(this->m_frontLeftWingDamage);
    memcpy(&this->m_frontRightWingDamage, &buffer[offset], sizeof(this->m_frontRightWingDamage));
    offset = offset + sizeof(this->m_frontRightWingDamage);
    memcpy(&this->m_rearWingDamage, &buffer[offset], sizeof(this->m_rearWingDamage));
    offset = offset + sizeof(this->m_rearWingDamage);
    memcpy(&this->m_floorDamage, &buffer[offset], sizeof(this->m_floorDamage));
    offset = offset + sizeof(this->m_floorDamage);
    memcpy(&this->m_diffuserDamage, &buffer[offset], sizeof(this->m_diffuserDamage));
    offset = offset + sizeof(this->m_diffuserDamage);
    memcpy(&this->m_sidepodDamage, &buffer[offset], sizeof(this->m_sidepodDamage));
    offset = offset + sizeof(this->m_sidepodDamage);
    memcpy(&this->m_drsFault, &buffer[offset], sizeof(this->m_drsFault));
    offset = offset + sizeof(this->m_drsFault);
    memcpy(&this->m_gearBoxDamage, &buffer[offset], sizeof(this->m_gearBoxDamage));
    offset = offset + sizeof(this->m_gearBoxDamage);
    memcpy(&this->m_engineDamage, &buffer[offset], sizeof(this->m_engineDamage));
    offset = offset + sizeof(this->m_engineDamage);
    memcpy(&this->m_engineMGUHWear, &buffer[offset], sizeof(this->m_engineMGUHWear));
    offset = offset + sizeof(this->m_engineMGUHWear);
    memcpy(&this->m_engineESWear, &buffer[offset], sizeof(this->m_engineESWear));
    offset = offset + sizeof(this->m_engineESWear);
    memcpy(&this->m_engineCEWear, &buffer[offset], sizeof(this->m_engineCEWear));
    offset = offset + sizeof(this->m_engineCEWear);
    memcpy(&this->m_engineICEWear, &buffer[offset], sizeof(this->m_engineICEWear));
    offset = offset + sizeof(this->m_engineICEWear);
    memcpy(&this->m_engineMGUKWear, &buffer[offset], sizeof(this->m_engineMGUKWear));
    offset = offset + sizeof(this->m_engineMGUKWear);
    memcpy(&this->m_engineTCWear, &buffer[offset], sizeof(this->m_engineTCWear));
    offset = offset + sizeof(this->m_engineTCWear);
    memcpy(&this->m_engineBlown, &buffer[offset], sizeof(this->m_engineBlown));
    offset = offset + sizeof(this->m_engineBlown);
    memcpy(&this->m_engineSeized, &buffer[offset], sizeof(this->m_engineSeized));
    offset = offset + sizeof(this->m_engineSeized);

    return offset;
  }
};

struct PacketCarDamageData {
  PacketHeader m_header; // Header
  CarDamageData m_carDamageData[22];

  unsigned long get(char* buffer) {
    unsigned long offset = this->m_header.get(buffer);
    for (int i = 0; i < 22; i++) {
      offset = this->m_carDamageData[i].get(buffer, offset);
    }

    return offset;
  }
};

struct LapHistoryData {
  uint32_t m_lapTimeInMS; // Lap time in milliseconds
  uint16_t m_sector1TimeInMS; // Sector 1 time in milliseconds
  uint16_t m_sector2TimeInMS; // Sector 2 time in milliseconds
  uint16_t m_sector3TimeInMS; // Sector 3 time in milliseconds
  uint8_t m_lapValidBitFlags; // 0x01 bit set-lap valid, 0x02 bit set-sector 1 valid
  // 0x04 bit set-sector 2 valid, 0x08 bit set-sector 3 valid

  unsigned long get(char* buffer, unsigned long offset) {
    memcpy(&this->m_lapTimeInMS, &buffer[offset], sizeof(this->m_lapTimeInMS));
    offset += sizeof(this->m_lapTimeInMS);
    memcpy(&this->m_sector1TimeInMS, &buffer[offset], sizeof(this->m_sector1TimeInMS));
    offset += sizeof(this->m_sector1TimeInMS);
    memcpy(&this->m_sector2TimeInMS, &buffer[offset], sizeof(this->m_sector2TimeInMS));
    offset += sizeof(this->m_sector2TimeInMS);
    memcpy(&this->m_sector3TimeInMS, &buffer[offset], sizeof(this->m_sector3TimeInMS));
    offset += sizeof(this->m_sector3TimeInMS);
    memcpy(&this->m_lapValidBitFlags, &buffer[offset], sizeof(this->m_lapValidBitFlags));
    offset += sizeof(this->m_lapValidBitFlags);

    return offset;
  }
};

struct TyreStintHistoryData {
  uint8_t m_endLap; // Lap the tyre usage ends on (255 of current tyre)
  uint8_t m_tyreActualCompound; // Actual tyres used by this driver
  uint8_t m_tyreVisualCompound; // Visual tyres used by this driver

  unsigned long get(char* buffer, unsigned long offset) {
    memcpy(&this->m_endLap, &buffer[offset], sizeof(this->m_endLap));
    offset += sizeof(this->m_endLap);
    memcpy(&this->m_tyreActualCompound, &buffer[offset], sizeof(this->m_tyreActualCompound));
    offset += sizeof(this->m_tyreActualCompound);
    memcpy(&this->m_tyreVisualCompound, &buffer[offset], sizeof(this->m_tyreVisualCompound));
    offset += sizeof(this->m_tyreVisualCompound);
    return offset;
  }
};

struct PacketSessionHistoryData {
  PacketHeader m_header; // Header
  uint8_t m_carIdx; // Index of the car this lap data relates to
  uint8_t m_numLaps; // Num laps in the data (including current partial lap)
  uint8_t m_numTyreStints; // Number of tyre stints in the data
  uint8_t m_bestLapTimeLapNum; // Lap the best lap time was achieved on
  uint8_t m_bestSector1LapNum; // Lap the best Sector 1 time was achieved on
  uint8_t m_bestSector2LapNum; // Lap the best Sector 2 time was achieved on
  uint8_t m_bestSector3LapNum; // Lap the best Sector 3 time was achieved on
  LapHistoryData m_lapHistoryData[100]; // 100 laps of data max
  TyreStintHistoryData m_tyreStintsHistoryData[8];

  void get(char* buffer) {
    unsigned long offset = this->m_header.get(buffer);
    memcpy(&this->m_carIdx, &buffer[offset], sizeof(this->m_carIdx));
    offset += sizeof(this->m_carIdx);
    memcpy(&this->m_numLaps, &buffer[offset], sizeof(this->m_numLaps));
    offset += sizeof(this->m_numLaps);
    memcpy(&this->m_numTyreStints, &buffer[offset], sizeof(this->m_numTyreStints));
    offset += sizeof(this->m_numTyreStints);
    memcpy(&this->m_bestLapTimeLapNum, &buffer[offset], sizeof(this->m_bestLapTimeLapNum));
    offset += sizeof(this->m_bestLapTimeLapNum);
    memcpy(&this->m_bestSector1LapNum, &buffer[offset], sizeof(this->m_bestSector1LapNum));
    offset += sizeof(this->m_bestSector1LapNum);
    memcpy(&this->m_bestSector2LapNum, &buffer[offset], sizeof(this->m_bestSector2LapNum));
    offset += sizeof(this->m_bestSector2LapNum);
    memcpy(&this->m_bestSector3LapNum, &buffer[offset], sizeof(this->m_bestSector3LapNum));
    offset += sizeof(this->m_bestSector3LapNum);
    for (int i = 0; i < 100; i++) {//m_numLaps
      offset = this->m_lapHistoryData[i].get(buffer, offset);
    }
    for (int i = 0; i < 8; i++) {
      offset = this->m_tyreStintsHistoryData[i].get(buffer, offset);// m_numTyreStints
    }
  }
};