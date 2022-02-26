const fetch = require('node-fetch')
var headers = {
    "user-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.157 Safari/537.36"
}
fetch("http://requestbin.net/r/15qbnjdu" ,{ method: 'GET', headers: headers}).then(result => result.text()).then(text => {
    console.log(text)
})