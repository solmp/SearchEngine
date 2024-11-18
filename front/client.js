const express = require("express");
var request = require("request");
const app = express();
const server_host = "http://127.0.0.1:8080/";

app.use(express.json());

app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

app.post("/api", (req, res) => {
  const { type, data } = req.body;
  const dataToSend = { type: type, data: data };
  //发送请求
  request.post(
    {
      url: server_host,
      json: dataToSend,
    },
    (error, response, body) => {
      if (error) {
        res.status(500).send("Error fetching data from backend");
        return;
      }
      res.send(body);
    }
  );
});

app.listen(3000, "0.0.0.0", () => {
  console.log("Server is running on port 3000");
});
