const Curl = require('node-libcurl').Curl;
let curl = new Curl();

// https://stackoverflow.com/questions/6819143/curl-equivalent-in-node-js
curl.setOpt(Curl.option.URL, process.argv[2])
curl.setOpt(Curl.option.FOLLOWLOCATION, true)
curl.setOpt(Curl.option.USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.157 Safari/537.36")

curl.on( 'end', function( statusCode, body, headers ) {
    const jsonstr = body.split("window['SIGI_STATE']=").pop().split(";window['SIGI_RETRY']")[0]; 
    jsonData = JSON.parse(jsonstr)
    process.stdout.write(jsonData["ItemList"]["video"]["preloadList"][0]["url"])
    this.close();
});

curl.on( 'error', function( err, curlErrorCode ) {

    console.error( err.message );
    console.error( '---' );
    console.error( curlErrorCode );

    this.close();

});

curl.perform();