const net = require("net");

const PORT = 8080;
const HTTP_PORT = 8081;

// Class to hold and manage the data
class Server {
  constructor(serverIP, maxPlayers, isQueueServer)
  {
    this.serverIP = serverIP || "";
    this.players = [];
    this.maxPlayers = maxPlayers || 0;
    this.isQueueServer = isQueueServer || false;
  }

  addPlayer(playerName)
  {
    if(this.players.length < this.maxPlayers)
    {
      this.players.push(playerName);
      this.notifyUpdate();
      return {status: "success", message: "Player added.", statusCode: 200};
    }
    else
    {
      return {status: "error", message: "Server is full.", statusCode: 400};
    }
  }

  removePlayer(playerName) {
    const index = this.players.indexOf(playerName);
    if (index !== -1) {
      this.players.splice(index, 1);
      this.notifyUpdate();
      return { status: "success", message: "Player removed." };
    } else {
      return { status: "error", message: "Player not found." };
    }
  }

  notifyUpdate() {
    // Send the updated data to this server itself
    this.sendData(this);

    // If this is NOT the queue server, send the data to the queue server as well
    if (!this.isQueueServer && queueServer) {
      queueServer.sendData(this);
    }
  }

  sendData(data) {
    if (this.socket) {
      try {
        this.socket.write(JSON.stringify(data) + "\n");
      } catch (err) {
        console.error(`Error sending data to server ${this.serverIP}:`, err);
      }
    }
  }

  setSocket(socket) {
    this.socket = socket;
  }
}

let connections = [];
let servers = new Map();
const queueServer = null;

const tcpServer = net.createServer((socket) => {
  console.log("Server connected");

  socket.on("data", (data) => {
    try {
      const message = JSON.parse(data.toString());

      // Handle initial server registration
      if (message.serverIP && message.maxPlayers !== undefined && message.isQueueServer !== undefined) {
        const server = new Server(
          message.serverIP,
          message.maxPlayers,
          message.isQueueServer
        );
        server.setSocket(socket); // Associate the socket with the server instance
        servers.set(message.serverIP, server);

        if (server.isQueueServer) {
          queueServer = server;
        }

        console.log(
          `Server registered: ${message.serverIP}, Max Players: ${message.maxPlayers}, Queue Server: ${message.isQueueServer}`
        );

        // Acknowledge registration
        socket.write(
          JSON.stringify({ status: "success", message: "Server registered." }) +
            "\n"
        );

        return;
      }

      // Handle player addition/removal
      if (message.command === "addPlayer" && message.serverIP) {
        const server = servers.get(message.serverIP);
        if (server) {
          const response = server.addPlayer(message.playerName);
          socket.write(JSON.stringify(response) + "\n");
        } else {
          socket.write(
            JSON.stringify({ status: "error", message: "Server not found." }) +
              "\n"
          );
        }
      } else if (message.command === "removePlayer" && message.serverIP) {
        const server = servers.get(message.serverIP);
        if (server) {
          const response = server.removePlayer(message.playerName);
          socket.write(JSON.stringify(response) + "\n");
        } else {
          socket.write(
            JSON.stringify({ status: "error", message: "Server not found." }) +
              "\n"
          );
        }
      }
    } catch (err) {
      console.error("Error processing message:", err);
      socket.write(
        JSON.stringify({ status: "error", message: "Invalid data format." }) +
          "\n"
      );
    }
  });

  socket.on("end", () => {
    console.log("Server disconnected");
    connections = connections.filter((conn) => conn !== socket);

    // Remove server instance if socket is associated
    for (const [ip, server] of servers.entries()) {
      if (server.socket === socket) {
        servers.delete(ip);
        console.log(`Server removed: ${ip}`);
        if (server.isQueueServer) {
          queueServer = null;
          console.log("Queue server disconnected");
        }
        break;
      }
    }
  });

  socket.on("error", (err) => {
    console.error("Socket error:", err);
  });

  connections.push(socket);
});

tcpServer.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`);
});

// // Create HTTP server to handle POST requests
// const httpServer = http.createServer((req, res) => {
//   if (req.method === "POST" && req.url === "/update") {
//     let body = "";

//     req.on("data", (chunk) => {
//       body += chunk;
//     });

//     req.on("end", () => {
//       try {
//         const updatedData = JSON.parse(body);
//         playServer.updateData(updatedData);
//         console.log("Data updated:", updatedData);

//         // Notify all connected clients with the updated data
//         connections.forEach((socket) => {
//           socket.write(playServer.getData() + "\n");
//         });

//         res.statusCode = 200;
//         res.setHeader("Content-Type", "application/json");
//         res.end(JSON.stringify({ status: "success", data: updatedData }));
//       } catch (err) {
//         console.error("Error parsing JSON:", err);
//         res.statusCode = 400;
//         res.setHeader("Content-Type", "application/json");
//         res.end(JSON.stringify({ status: "error", message: "Invalid JSON" }));
//       }
//     });
//   } else {
//     res.statusCode = 404;
//     res.end();
//   }
// });

// httpServer.listen(HTTP_PORT, () => {
//   console.log(`HTTP server listening on port ${HTTP_PORT}`);
// });
