const express = require('express');
const router = express.Router();
const asiakas=require('../models/asiakas_model');

router.get('/',function(request,response){
    asiakas.getAll(function(err, result){
        if(err){
            response.json(err);
        }
        else
        {
            //palautetaan array
            response.json(result);
        }
    })
});

router.get('/:id',function(request, response){
    asiakas.getById(request.params.id,function(err, result){
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


router.post('/',function(request,response){
    asiakas.add(request.body, function(err,result){
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

router.put('/:id',function(request, response){
    asiakas.update(request.params.id, request.body, function(err,result){
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

router.delete('/:id',function(request,response){
    asiakas.delete(request.params.id, function(err,result){
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

module.exports=router;