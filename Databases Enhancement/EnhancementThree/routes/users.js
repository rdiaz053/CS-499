var express = require('express');
var router = express.Router();

/* GET customers. */
router.get('/customers', function(req, res) {
  var db = req.db;
  var collection = db.get('customers');
  collection.find({},{},function(e,docs){
    res.json(docs);
  });
});

/* POST to addUser. */
router.post('/addUser', function(req, res) {
  var db = req.db;
  var collection = db.get('customers');
  collection.insert(req.body, function(err, result){
    res.send(
      (err === null) ? { msg: '' } : { msg: err }
    );
  });
});

/* PUT to updateUser. */
router.put('/updateUser/:id', function(req, res) {
  var db = req.db;
  var collection = db.get('customers');
  var data = req.body
  var userToUpdate = req.params.id;
  collection.update({'_id' : userToUpdate}, {'$set': data}, function(err) {
    res.send((err === null) ? { msg: '' } : { msg:'error: ' + err });
  });
});

/* DELETE to deleteUser. */
router.delete('/deleteuser/:id', function(req, res) {
  var db = req.db;
  var collection = db.get('customers');
  var userToDelete = req.params.id;
  collection.remove({ '_id' : userToDelete }, function(err) {
    res.send((err === null) ? { msg: '' } : { msg:'error: ' + err });
  });
});

module.exports = router;
