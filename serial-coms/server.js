'use strict';

// const SerialPort = require('serialport');
// const port = new SerialPort('/dev/ttyUSB1', {
//   baudRate: 57600
// });
// const Readline = SerialPort.parsers.Readline;
// const parser = new Readline();
// port.pipe(parser);

const path = require('path');
const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const app = express();
app.use(express.static(path.join(__dirname, 'public')));
app.use(cors());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

app.post('/goto', (req, res) => {
  console.log(req.params);
  console.log(req.body.position);
  console.log(req.body);
  res.send('holi');

});



app.listen(8081, () => console.log('Example app listening on port 8081!'));
