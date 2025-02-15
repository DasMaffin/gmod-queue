const net = require("net");
const http = require("http");

const PORT = 8080;
const HTTP_PORT = 8081;

// Class to hold and manage the data
class DataManager {
  constructor() {
    var d = new Date();
    this.data = { message: "Initial data", timestamp: new Date(d.getFullYear(), d.getMonth(), d.getDay(), d.getHours() + 1, d.getMinutes(), d.getSeconds(), d.getMilliseconds()) };
  }

  // Method to update the data and set the timestamp
  updateData(newData) {
    var d = new Date();
    this.data = { ...newData, timestamp: new Date(d.getFullYear(), d.getMonth(), d.getDay(), d.getHours() + 1, d.getMinutes(), d.getSeconds(), d.getMilliseconds()) };
  }

  // Method to get the current data in JSON format
  getData() {
    return JSON.stringify(this.data);
  }
}

let connections = [];
const dataManager = new DataManager();

// Create TCP server
const server = net.createServer((socket) => {
  console.log("Client connected");
  connections.push(socket); // Keep track of all clients

  // Send current data to the client upon connection
  socket.write(dataManager.getData() + "\n");

  socket.on("end", () => {
    console.log("Client disconnected");
    connections = connections.filter((conn) => conn !== socket);
  });

  socket.on("error", (err) => {
    console.error("Socket error:", err);
  });
});

server.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`);
});

// Create HTTP server to handle POST requests
const httpServer = http.createServer((req, res) => {
  if (req.method === "POST" && req.url === "/update") {
    let body = "";

    req.on("data", (chunk) => {
      body += chunk;
    });

    req.on("end", () => {
      try {
        const updatedData = JSON.parse(body);
        dataManager.updateData(updatedData);
        console.log("Data updated:", updatedData);

        // Notify all connected clients with the updated data
        connections.forEach((socket) => {
          socket.write(dataManager.getData() + "\n");
        });

        res.statusCode = 200;
        res.setHeader("Content-Type", "application/json");
        res.end(JSON.stringify({ status: "success", data: updatedData }));
      } catch (err) {
        console.error("Error parsing JSON:", err);
        res.statusCode = 400;
        res.setHeader("Content-Type", "application/json");
        res.end(JSON.stringify({ status: "error", message: "Invalid JSON" }));
      }
    });
  } else {
    res.statusCode = 404;
    res.end();
  }
});

httpServer.listen(HTTP_PORT, () => {
  console.log(`HTTP server listening on port ${HTTP_PORT}`);
});
