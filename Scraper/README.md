# AWS Kubernetes Web Scraper

<img src="https://user-images.githubusercontent.com/60249504/148848171-5d554da6-632b-496e-b2d1-39baba97503f.gif" alt="Img Couldn't Load" width="500">

The actual scraper implementation is not included, but the file name is pyscraper.js (Philip Yazvin Scraper) it uses puppeteer to fetch the dom of the requested site. Then the dom is scrubbed, and cleaned. Then through recursive traversal and json condensing readable information is presented to the user.

The docker files are buildable, and the kubernetes is deployable, also you're going to have to provide your own AWS server for storing the information. A credentials.json is included where you would enter your security information, and modify the code to use your AWS server.

Also for the kubernetes services you can use a real ip address, or you can forward a port to the service, ect. If you watch the video you will see how.
