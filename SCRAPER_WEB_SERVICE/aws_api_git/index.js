const axios = require("axios").default;
const express = require("express");
require("dotenv").config();
const fs = require("fs");
const server = express();
const AWS = require('aws-sdk');
const bucket_name = "pyscrapeddata";
const interface = new AWS.S3();
interface.config.loadFromPath('./credentials.json');

server.use(express.json());
server.post('/', (req, res) => {
    console.log("request recieved");
    axios.post("http://scraper-scraper-service:7021/", { url: req.body.url }).then(data => {
        var result = JSON.stringify(data.data);
        var key = String(req.body.url);
        var key=key.slice(8);
        const upload_data = {
            Bucket: bucket_name,
            Body: result,
            Key: key,
            ContentType: 'application/json'
        }
        interface.upload(upload_data).send();
        console.log("data uploaded");
        res.send(data.data);
    });

});


server.listen(7022, () => {
    console.log("Server Started on Port 7022 (Local To Container)");
});




