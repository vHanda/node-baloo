# Node-Baloo

Node-Baloo provides node.js bindings for [Baloo](https://projects.kde.org/projects/frameworks/baloo/).

```javascript
var Baloo = require('baloo');

var query = new Baloo.Query('keyword');
query.exec(function(results) {
    results.forEach(function(filePath) {
        console.log(filePath);
    });
});
```

