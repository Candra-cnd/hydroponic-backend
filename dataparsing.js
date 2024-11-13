fetch('http://localhost:3000/data')
    .then(response => response.json())
    .then(data => {
        console.log('Suhu Maks: ', data.suhumax);
        console.log('Suhu Min: ', data.suhumin);
        console.log('Rata-rata Suhu: ', data.suhurata);
        console.log('Data Suhu Max Humid Max: ', data.nilai_suhu_max_humid_max);
        console.log('Bulan-Tahun Max: ', data.month_year_max);
    })
    .catch(error => console.error('Error:', error));