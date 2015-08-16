var Baloo = require('../build/Release/baloo');

var sinon = require('sinon');

suite('Query', function() {
    var sut;

    suite('#constructor', function() {
        test('Should throw TypeError on no arguments', function() {
            try {
                var spy = sinon.spy(Baloo, 'Query');
                var sut = new Baloo.Query();
            } catch(err) {}
            sinon.assert.threw(spy, 'TypeError');
            spy.restore();
        });

        test('Should throw TypeError on invalid argument', function() {
            try {
                var spy = sinon.spy(Baloo, 'Query');
                var sut = new Baloo.Query(42);
            } catch(err) {}
            sinon.assert.threw(spy, 'TypeError');
            spy.restore();
        });
    });

    suite('#exec', function() {
        setup(function() {
            sut = new Baloo.Query('test');
        });

        test('Should throw TypeError on no arguments', function() {
            try {
                var spy = sinon.spy(sut, 'exec');
                sut.exec(); 
            } catch(err) {}
            sinon.assert.threw(spy, 'TypeError');
        });

        test('Should throw TypeError on invalid argument', function() {
            try {
                var spy = sinon.spy(sut, 'exec');
                sut.exec(1); 
            } catch(err) {}
            sinon.assert.threw(spy, 'TypeError');
        });
    });
});

