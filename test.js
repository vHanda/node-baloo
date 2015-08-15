var Baloo = require('./build/Release/baloo');

var query = new Baloo.Query("coldplay");
query.exec(function(results) {
    results.forEach(function(filePath) {
        console.log(filePath);
    });
});
