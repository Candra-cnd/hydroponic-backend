const mqtt = require('mqtt');
const dataStorage = require('./dataStorage');

// Koneksi ke broker MQTT
const mqttClient = mqtt.connect('mqtt://broker.hivemq.com');

mqttClient.on('connect', () => {
  console.log('Terhubung ke broker MQTT');
  mqttClient.subscribe('hidroponik/sensor');
  mqttClient.subscribe('hidroponik/control');
});

mqttClient.on('message', (topic, message) => {
  if (topic === 'hidroponik/sensor') {
    const data = JSON.parse(message.toString());
    dataStorage.updateSensorData({
      suhu: data.suhu,
      kelembapan: data.kelembapan,
      ph: data.ph,
      kekeruhan: data.kekeruhan,
    });
  } else if (topic === 'hidroponik/control') {
    const controlData = JSON.parse(message.toString());
    dataStorage.updatePumpStatus(controlData.pompa);
  }
});

module.exports = mqttClient;
