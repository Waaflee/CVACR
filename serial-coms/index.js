'use strict';
const http = require('http');
const url = require('url');
const connect = require('connect');
const serveStatic = require('serve-static');
const SerialPort = require('serialport');

const port = new SerialPort('/dev/ttyUSB1', {
  baudRate: 57600
});
const Readline = SerialPort.parsers.Readline;
const parser = new Readline();
port.pipe(parser);

connect().use(serveStatic(__dirname)).listen(8080, function() {
  console.log('Server running on 8080...');
});
http.createServer(function(req, res) {
  res.setHeader("Access-Control-Allow-Origin", "http://localhost:8080");
  res.setHeader("Access-Control-Allow-Origin", "http://localhost:8081");
  res.writeHead(200, {
    'Content-Type': 'text/html'
  });
  let q = url.parse(req.url, true).query;
  let position = q.position;
  let speed = q.speed
  let response = {
    'position': position,
    'speed': speed
  }
  console.log(JSON.stringify(response));
  if (q.homing == 1) {
    port.write(`:H\n`);
  } else {
    port.write(`:S0:${response.speed}\n`);
    port.write(`:R0:${response.position}\n`);
  };
  res.end(JSON.stringify(response));
}).listen(8081);



parser.on('data', (data) => {
  console.log(data);
  // port.write(`:D00\n`);
});


setTimeout(() => {
  port.write(':h\n')
}, 2500);
