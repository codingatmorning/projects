<img src="https://user-images.githubusercontent.com/60249504/147365454-ec78a07c-8121-4341-b229-825325cf4b92.gif" alt="Img Couldn't Load" width="500">

## Description - implementation of KDBVH-Tree

■ It stores a Bounding Volume in N dimensions (x,y,z,w,...)  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- 2D = Square, 3d = Cube, 4d = Tesseract, .... (Hyper Cube)  

■ Simply Inherit BVH class, and your Object is now storable in a BVH Tree  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- Just define get_bounds()  

■ The Tree is Space-Filling which means worse case access time is log(n)  

## Build

- Build Script included ./build.sh
  - For different Compilers change the code to compiler equivalent
- Compile with -DExample to see Example Usage
      
## Applications 
- :collision: Can be used in a lot of applications, and uses
  - Spacial Database, Computer Graphics, Mathametical Visualization...

<h1 align="center"><project-name></h1>

<p align="center"><project-description></p>

## Links

- [Repo](https://github.com/Rohit19060/<project-name> "<project-name> Repo")

- [Live](<Homepage url> "Live View")

- [Bugs](https://github.com/Rohit19060/<project-name>/issues "Issues Page")

- [API](<API Link> "API")

## Screenshots

![Home Page](/screenshots/1.png "Home Page")

![](/screenshots/2.png)

![](/screenshots/3.png)

## Available Commands

In the project directory, you can run:

### `npm start" : "react-scripts start"`,

The app is built using `create-react-app` so this command Runs the app in Development mode. Open [http://localhost:3000](http://localhost:3000) to view it in the browser. You also need to run the server file as well to completely run the app. The page will reload if you make edits.
You will also see any lint errors in the console.

### `"npm run build": "react-scripts build"`,

Builds the app for production to the `build` folder. It correctly bundles React in production mode and optimizes the build for the best performance. The build is minified and the filenames include the hashes. Your app will be ready to deploy!

### `"npm run test": "react-scripts test"`,

Launches the test runner in the interactive watch mode.

### `"npm run dev": "concurrently "nodemon server" "npm run start"`,

For running the server and app together I am using concurrently this helps a lot in the MERN application as it runs both the server (client and server) concurrently. So you can work on them both together.

### `"serve": "node server"`

For running the server file on you can use this command.

### `npm run serve`

## Built With

- JavaScript
- Node
- NPM
- Webpack
- HTML
- CSS

## Future Updates

- [ ] Reliable Storage

## Author

**Rohit Jain**

- [Profile](https://github.com/rohit19060 "Rohit jain")
- [Email](mailto:rohitjain19060@gmail.com?subject=Hi "Hi!")
- [Website](https://kingtechnologies.in "Welcome")

## 🤝 Support

Contributions, issues, and feature requests are welcome!

Give a ⭐️ if you like this project!
