const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
    console.log(req.query["url"])
    var exec = require('child_process').exec;
    exec("../CPP/a.out \"" + req.query.url + "\"", function(error, stdout, stderr){ res.send("<video src=\""+stdout+"\">") });


})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})