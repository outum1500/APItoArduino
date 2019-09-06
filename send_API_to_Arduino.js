var SerialPort = require('serialport');
var serialPort = new SerialPort("COM3", {baudRate: 9600}); // 아두이노 연결
var http = require('http');
var UrlParser = require('url');
var jsdom = require('jsdom');
$ = require('jquery')(new jsdom.JSDOM().window);

var apiURI = "http://api.openweathermap.org/data/2.5/weather?q="+"Jeju"+"&appid="+"e1a2828a89f0aa6f57e4dd618f2016cf";

serialPort.on("open",function() { // 아두이노와 연결되었으면 콘솔에 문구띄움
    console.log("open success")
});

$(function(){
    $.ajax({
        url: apiURI,
        dataType: "json",
        type: "GET",
        async: "false",
        success: function(resp) {
            //console.log("현재온도 : "+ (resp.main.temp- 273.15) );
            //console.log("날씨 : "+ resp.weather[0].main );
            
            var temp = Math.round((resp.main.temp-273.15)*10)/10;
            var weather = resp.weather[0].main;
            var name = resp.name;
            name = name.toString();
            weather = weather.toString();
            temp = temp.toString();
            console.log(temp + " " + weather + "   Loc: " + name);

            //var result = temp + "9" + resp.weather[0].main;
            
            setInterval(function() { // 2초마다 아두이노에게 문자열을 전송하는 예
                serialPort.write(temp + " " + weather + "Loc:" + name, function() { });   
             }, 2000);
        }
    })
})
