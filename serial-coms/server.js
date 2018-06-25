'use strict';

const SerialPort = require('serialport');
const port = new SerialPort('/dev/ttyUSB0', {
  baudRate: 57600
});
const Readline = SerialPort.parsers.Readline;
const parser = new Readline();
port.pipe(parser);

const path = require('path');
const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const app = express();

const server = require('http').Server(app);
const io = require('socket.io')(server);

// EXPRESS SETUP
app.use(express.static(path.join(__dirname, 'public')));
app.use(cors());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

//EXPRESS REQUESTS HANDLING

app.post('/goto', (req, res) => {
  console.log(req.body);
  console.log('Position = ', req.body.position);
  console.log('Motor = ', req.body.motor);
  let response = {
    'message': 'Going to realtive position...',
    'position': req.body.position,
    'motor': req.body.motor
  };
  res.send(JSON.stringify(response));
  port.write(`:R${req.body.motor}:${req.body.position}\n`);

});

app.post('/speed', (req, res) => {
  console.log(req.body);
  console.log('Speed = ', req.body.speed);
  console.log('Motor = ', req.body.motor);
  let response = {
    'message': 'Setting speed',
    'speed': req.body.speed,
    'motor': req.body.motor
  };
  res.send(JSON.stringify(response));
  port.write(`:S${req.body.motor}:${req.body.speed}\n`);
});

app.post('/homing', (req, res) => {
  console.log(req.body);
  console.log('Homing = ', req.body.homing);
  let response = {
    'message': 'Homing',
    'motor': 'Every One'
  };
  res.send(JSON.stringify(response));
  port.write(':H\n');
});

app.post('/diag', (req, res) => {
  console.log(req.body);
  console.log('motor = ', req.body.motor);
  let response = {
    'diagnostic on motor': req.body.motor
  };
  res.send(JSON.stringify(response));
  port.write(`:D${req.body.motor}\n`);
});


///SOCKET.IO///////////////////////////////////////////////////////////////////
io.on('connection', function (socket) {
  parser.on('data', (data) => {
    console.log(data);
    socket.emit('uart message', { message: data + '\n' });
  });
});


//SERIALPORT

//BOOTSTRAP
// app.listen(8080, () => console.log('Serial-coms listening on port 8080!'));
server.listen(8080, ()=> {
  console.log('Serial-coms listening on port 8080!');
});
