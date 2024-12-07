# Localization App

An IoT application designed to provide real-time location tracking within a specific floor using Wi-Fi signal strength. This solution integrates hardware, machine learning models, and both mobile and web interfaces to deliver precise and actionable location data.

---

## Table of Contents

1. [Features](#features)
2. [Requirements & Workflow](#requirements--workflow)  
   - [Hardware Requirements](#hardware-requirements)  
   - [AI & Server Workflow](#ai--server-workflow)  
3. [AI Model Dependencies](#ai-model-dependencies)
4. [Prerequisites](#prerequisites)
5. [How to Get Started](#how-to-get-started)
6. [Contributions & Support](#contributions--support)

---

## Features

- **Real-Time Localization**: Tracks and updates the current location on a specific floor.  
- **Replay Functionality**: View the last 10 locations for detailed analysis.  
- **Hardware Integration**: Utilizes ESP chips for Wi-Fi signal strength collection and communication.  
- **Cross-Platform Access**: Displays location on both mobile and web applications.  

---

## Requirements & Workflow  

### Hardware Requirements
The solution uses **ESP chips**, equipped with wireless communication modules. These chips are responsible for:  
1. **Wi-Fi Signal Strength Collection**:  
   - Readings are taken via ESP chips and stored in an Excel sheet using [ArduSpreadsheet](https://circuitjournal.com/arduino-serial-to-spreadsheet).  
   - This data is essential for training the machine-learning model.  
2. **Data Communication**:  
   - Establishes a WebSocket connection with the server to transmit Wi-Fi strength data.  

### AI & Server Workflow
1. **Data Collection**: Wi-Fi signal strength is logged and stored at `/model/all_data.csv`.  
2. **Model Prediction**: The server leverages the XGBoost model to determine the user's location based on the incoming data.  
3. **Location Visualization**:  
   - The processed location data is displayed on mobile and web apps.  
   - Historical data (last 10 locations) can be replayed for review.

---

## AI Model Dependencies

Ensure the following Python libraries are installed to run the AI model:

```bash
joblib==1.1.0
numpy==1.22.3
pandas==1.4.1
python-dateutil==2.8.2
pytz==2021.3
scikit-learn==1.0.2
scipy==1.8.0
six==1.16.0
sklearn==0.0
threadpoolctl==3.1.0
xgboost==1.5.2
