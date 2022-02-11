const HTTPS = require("https");
const scraper = require("./pyscraper"); //Philip Yazvin
const fs = require("fs");
const express = require("express");
const server = express();
const port = 7021;
(async () => {
    await scraper.start();
})();

server.use(express.json());
server.post('/', (req, res) => {
    try {
        console.log("start scraping");
        scraper.get(req.body.url).then((data) => { res.send(data); });
        console.log("finished scraping");
    }
    catch (e) {
        res.send(e);
    }
});


const listener = server.listen(port, () => {
    console.log(`Server Started on ${port} (Local to Container)`)
})



