const express = require('express');
const bodyParser = require('body-parser');
const dataStorage = require('./dataStorage'); // Import modul penyimpanan data
require('./mqttClient'); // Import dan jalankan modul MQTT

const app = express();
app.use(bodyParser.json());
app.use(express.json());

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/dataparsing.html');
});


// Endpoint untuk mendapatkan data dalam format JSON
app.get('/api/data', (req, res) => {
  res.json(dataStorage.getSensorData());
});

// Endpoint untuk mendapatkan data JSON
app.get('/data', (req, res) => {
    const data = {
      suhumax: 36,
      suhumin: 21,
      suhurata: 28.35,
      nilai_suhu_max_humid_max: [
        {
          idx: 101,
          suhun: 36,
          humid: 36,
          kecerahan: 25,
          timestamp: "2010-09-18 07:23:48"
        },
        {
          idx: 226,
          suhun: 36,
          humid: 36,
          kecerahan: 27,
          timestamp: "2011-05-02 12:29:34"
        }
      ],
      month_year_max: [
        {
          month_year: "9-2010"
        },
        {
          month_year: "5-2011"
        }
      ]
    };
    res.json(data);
  });

// Jalankan server di port 3000
app.listen(3000, () => {
  console.log('Server berjalan di http://localhost:3000');
});
