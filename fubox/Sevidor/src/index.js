const express = require('express')
const bodyParser = require('body-parser')
const cors = require('cors')
const app = express()


app.use(cors())
app.use(express.json())
const fs = require('fs')

const routes = require('../routes/routes.js')(app, fs)
const server = app.listen(3000, () => {
    console.log('listening on port %s...', server.address().port)
  });