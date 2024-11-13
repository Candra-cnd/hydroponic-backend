// Objek untuk menyimpan data sensor
let sensorData = {
    suhu: 28,
    kelembapan: 70,
    ph: 6.5,
    kekeruhan: 10,
    pompa: true
  };
  
  // Fungsi untuk memperbarui data sensor
  function updateSensorData(newData) {
    sensorData = { ...sensorData, ...newData };
  }
  
  // Fungsi untuk memperbarui status pompa
  function updatePumpStatus(status) {
    sensorData.pompa = status;
  }
  
  // Fungsi untuk mendapatkan data sensor
  function getSensorData() {
    return sensorData;
  }
  
  module.exports = {
    updateSensorData,
    updatePumpStatus,
    getSensorData
  };
  