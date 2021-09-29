//Call module
const net = require('net');
const readline = require('readline');

//Set input
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

//For clients Data arr
let clients = [];

//Function for Data Send to Clinet from another Client
function broadcast(Name, data)
{
	for(step = 0; step < clients.length; step++)
	{
		if(clients[step].name != Name)
			clients[step].client.write(data)
	}
}


function DeleteData(name)
{
	if(clients.length == 1)
		clients.pop();
	else
	{
		for(step = 0; step < clients.length; step++)
		{
			if(clients[step].name == name)
				clients.splice(step, 1)
		}
	}
	console.log('remaining Clients: ' + clients.length);
}

var server = net.createServer(function(socket){
	//When Client Connect to Server, Save the Client Data
	console.log("connection form : " + socket.remotePort);
	clients.push(
		{
			name : socket.remotePort,
			client : socket
		}
	);
	broadcast(socket.remotePort, "connection form : " + socket.remotePort)
	//When receive data from Client broadcast the data
	socket.on('data', function(data){
		var obj = JSON.parse(data.toString('utf-8'))
		broadcast(socket.remotePort, obj.Name + ': ' + obj.Data)
	})
	//When Client disconnected
	socket.on('end', function(){
		console.log(socket.remoteAddress + ':' + socket.remotePort)
		console.log(socket.remotePort + ' is disconnted.')
		broadcast(socket.remotePort, socket.remotePort + ' is disconnted.')
		DeleteData(socket.remotePort)
	})
	//When Server send the data
	rl.on('line', function(line)
	{
		socket.write(line)
	})
	
})
//Open the server at port 8080
server.listen(8080)