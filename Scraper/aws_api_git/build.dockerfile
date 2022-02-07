FROM node:16.2.0-alpine
WORKDIR /build
COPY index.js ./
COPY credentials.json ./
COPY package*.json ./
RUN npm install --production
EXPOSE 7021 7022
CMD ["node", "index.js"]
