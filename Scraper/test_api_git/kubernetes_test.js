const { default: axios } = require("axios");

//Host Machine Port 7022 is forwarded to Port 7022 on scraper-user-service
axios.post("http://localhost:7022", { url: "https://www.google.com/search?q=google+weather+new+york" }).then(e => {
    //We should Recieve our Scraped data
    console.log(e.data);
});

axios.post("http://localhost:7022", { url: "https://reddit.com" }).then(e => {
    //We should Recieve our Scraped data
    console.log(e.data);
});

axios.post("http://localhost:7022", { url: "https://www.businessinsider.com/" }).then(e => {
    //We should Recieve our Scraped data
    console.log(e.data);
});
