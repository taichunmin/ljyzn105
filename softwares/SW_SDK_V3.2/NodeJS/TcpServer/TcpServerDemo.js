var coroutine = require("coroutine");
var net = require('net');

function sleep(delay) {
    var start = new Date().getTime();
    while (new Date().getTime() < start + delay)
        ;
}

var buf1 = [0x53, 0x57, 0x00, 0x05,0xFF,0x24,0x02,0x01,0x2B]; //Set ActiveMode
//var buf1 = [0x53, 0x57, 0x00, 0x05,0xFF,0x24,0x05,0x1A,0x0F];  //Set RF Power RF = 0x24 / 26 dbm
//var buf1 = [0x53, 0x57, 0x00, 0x05,0xFF,0x24,0x05,0x07,0x22];    //Set RF Power RF = 0x07 / 7 dbm
//var buf1 = [0x53, 0x57, 0x00, 0x05,0xFF,0x24,0x02,0x01,0x2B];    //Set ActiveMode
//var buf1 = [0x53, 0x57, 0x00, 0x05,0xFF,0x24,0x02,0x00,0x2C];    //Set AnswerMode
//var buf1 = [0x53, 0x57, 0x00, 0x05,0xFF,0x3F,0x31,0x80,0x62];   //Set Freq.  US band
//var buf1 = [0x53, 0x57, 0x00, 0x05,0xFF,0x3F,0x4E,0x00,0xC5];   //Set Freq.  EU band
//var buf1 = [0x53, 0x57, 0x00, 0x05,0xFF,0x24,0x0A,0x00,0x24];   //ScanArea :  EPC
//var buf1 = [0x53, 0x57, 0x00, 0x05,0xFF,0x24,0x0A,0x01,0x23];   //ScanArea :  TID

var tcp_server = net.createServer();  // Create tcp server
var Sockets = {};
var SocketID = 1;
tcp_server.listen(65000,function (){
    console.log('tcp_server listening 65000');
});

// 处理客户端连接
tcp_server.on('connection',function (socket){
    console.log(socket.address());
    Sockets[SocketID] =socket;
    SocketID++;
    DealConnect(socket)
})

tcp_server.on('error', function (){
    console.log('tcp_server error!');
})

tcp_server.on('close', function () {
    console.log('tcp_server close!');
})

function DealConnect(socket){
    socket.on('data',function(data){
        //for(var i in Sockets){
        //    Sockets[i].write(data);
        //}
        console.log('data received:',data);
        //data[15]: TagNum   data[16]: singleTagLength( include 1 byte type and 1 byte ant and 1 byte rssi
        //data[17] == 0x01: Tag Type   data[18]: AntNum  data[19]..[30]: TagContent data[31]:RSSI
        //if data[17] == 0x81 with TimeStamp, last 6 bytes is time
    })
    socket.on('close', function () {
        console.log('client disconneted!');
    })
    socket.on("error", function (err) {
        console.log('client error disconneted!');
    });
}
