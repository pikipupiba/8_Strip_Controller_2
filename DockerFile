docker build -t LED-Plant-36 dockerfiles/
docker run LED-Plant-36 /script/to/run/tests
docker tag LED-Plant-36 https://github.com/pikipupiba/esp32-fastled-webserver/new/plant:5000/latest
docker push https://github.com/pikipupiba/esp32-fastled-webserver/new/plant:5000/latest
