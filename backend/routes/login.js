const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const kortti = require('../models/kortti_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');
const login=require('../models/asiakas_model');


router.get('/:id/2',function(request, response){
  login.getById(request.params.id,function(err, result){
      if(err){
          response.json(err);
      }
      else
      {
          //palautetaan objekti
          response.json(result[0]);
      }
  })
});

router.get('/:id',function(request, response){
  kortti.getById2(request.params.id,function(err, result){
      if(err){
          response.json(err);
      }
      else
      {
          //palautetaan objekti
          response.json(result[0]);
      }
  })
});

router.put('/:id',function(request, response){
  kortti.update2(request.params.id, request.body, function(err,result){
      if(err){
          response.json(err);
      }
      else
      {
          //palautetaan muokattujen rivien määrä
          response.json(result.affectedRows);
      } 
  })
});

router.post('/', 
  function(request, response) {
    if(request.body.username && request.body.password){
      const user = request.body.username;
      const pass = request.body.password;
      
        kortti.checkPassword(user, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pass,dbResult[0].pinkoodi, function(err,compareResult) {
                if(compareResult) {
                  console.log("success");
                  const token = generateAccessToken({ username: user });
                  response.setHeader('Content-Type', 'application/json'); 
                  response.send(token);
                }
                else {
                    console.log("wrong password");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("username or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
  dotenv.config();
  return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;