'use strict';
window.onload = () => {

  let messages = document.getElementsByName('messages')[0];
  let socket = io.connect('http://localhost:8080');
  socket.on('uart message', function (data) {
    console.log(data);
    messages.value += data.message;
    messages.scrollTop = messages.scrollHeight;
  });

  let position = document.getElementsByName('position')[0];
  let speed = document.getElementsByName('speed')[0];
  let data = document.getElementById('goTo');
  let data2 = document.getElementById('RPM');

  position.addEventListener("change", () => {
    data.innerHTML = 'Posición Eje: ' + position.value + '%';
    axios.post('/goto', {
        position: position.value,
        motor: 0
      })
      .then(function(response) {
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error);
      });
  });

  speed.addEventListener("change", () => {
    data2.innerHTML = 'RPM: ' + Math.round((speed.value / 100 * 30));
    axios.post('/speed', {
        speed: Math.round((speed.value / 100 * 30)),
        motor: 0
      })
      .then(function(response) {
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error);
      });
  });

  document.getElementsByName('homing')[0].addEventListener('click', () => {
    axios.post('/homing', {
        homing: 1
      })
      .then(function(response) {
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error);
      });
  });

  document.getElementsByName('info')[0].addEventListener('click', () => {
    axios.post('/diag', {
        motor: 0
      })
      .then(function(response) {
        console.log(response.data);
      })
      .catch(function(error) {
        console.log(error);
      });
  });
};
