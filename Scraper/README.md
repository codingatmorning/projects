# AWS Kubernetes Web Scraper

The actual scraper implementation is not included, but the file name is pyscraper.js (Philip Yazvin Scraper) it uses puppeteer to fetch the dom of the requested site. Then the dom is scrubbed, and cleaned. Then through recursive traversal and json condensing readble information is presented to the user.

The docker files are buildable, and the kubernetes is deployable, also you're going to have to provide your own AWS server for storing the information. A credentials json is included where you would enter your security information, and modify the code to use your AWS server.
