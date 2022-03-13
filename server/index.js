const { EventEmitter } = require('events');
const { Server } = require('ws');
const express = require('express');
const cors = require('cors');
const axios = require('axios');

const emitter = new EventEmitter();
let server = express();

server.use(cors());

server = server.listen(process.env.PORT || 80, () =>
  console.log(`Server is running on port ${process.env.PORT || 80}`),
);

const wss = new Server({ server });

let chip = null;
const devices = [];

const logTime = () => {
  const now = new Date();
  const time = `${now.getFullYear()}-${now.getMonth()}-${now.getDay()} ${now.getHours()}:${now.getMinutes()}:${now.getSeconds()}`;
  return time;
};

emitter.on('chipCall', (data) => {
  devices.forEach((device) => {
    try {
      device.send(data, { binary: false });
      console.log(`[${logTime()}] - MSG - ${data}`);
    } catch (error) {
      console.log(`[${logTime()}] - ERROR - Failed to send to a slave`);
    }
  });
});

wss.on('connection', function connection(ws, req) {
  switch (req.url) {
    case '/master':
      chip = ws;
      console.log(`[${logTime()}] - CHIP - Master Connected`);
      ws.on('message', function incoming(message) {
        console.log(`[${logTime()}] - CHIP - ${message}`);
        try {
          readings = JSON.parse(message);
        } catch (error) {
          console.log(`[${logTime()}] - ERROR - failed to parse JSON data`);
        }
        const data = [
          readings['El-lab'] || -100,
          readings['El-modarag'] || -100,
          readings['Redmi'] || -100,
          readings['youssef'] || -100,
          readings['Farouk'] || -100,
        ];
        console.log(data);
        let options = {
          strengthes: data,
        };
        // post request to the server using axios
        axios
          .post(
            'https://sbme-model-indoor-localization.herokuapp.com/',
            options,
          )
          .then(function (response) {
            console.log(
              `[${logTime()}] - DATA - data sent from server is ${
                response.data
              }`,
            );
            emitter.emit('chipCall', response.data);
          })
          .catch(function (error) {
            console.log(`[${logTime()}] - ERROR - couldn't fetch prediction`);
          });
      });
      break;
    case '/slave':
      console.log(`[${logTime()}] - DEVICE - New Device Connected`);
      devices.push(ws);
      break;
  }
});

wss.on('error', (error) => {
  console.log(`[${logTime()}] - ERROR - ${error}`);
});
