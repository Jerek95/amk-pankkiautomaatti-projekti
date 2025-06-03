const express = require('express');
const router = express.Router();
const tili=require('../models/tili_models');

router.get('/',function(request,response){
    tili.getAll(function(err, result){
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
    tili.getById(request.params.id,function(err, result){
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
    tili.add(request.body, function(err,result){
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
    tili.update(request.params.id, request.body, function(err,result){
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
    tili.delete(request.params.id, function(err,result){
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