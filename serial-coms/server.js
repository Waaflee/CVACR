'use strict';
const path = require('path');
const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const app = express();
app.use(express.static(path.join(__dirname, 'public')));
app.use(cors());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json())

app.post('/goto', (req, res) => {
  console.log(req.params);
  console.log(req.params.position);
  console.log(req.body);
  res.send('holi');

});



app.listen(8081, () => console.log('Example app listening on port 8081!'));
