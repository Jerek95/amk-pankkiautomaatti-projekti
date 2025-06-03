const express = require('express');
const router = express.Router();
const tilitapahtumat=require('../models/tilitapahtumat_model');

router.get('/',function(request,response){
    tilitapahtumat.getAll(function(err, result){
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
    tilitapahtumat.getById(request.params.id,function(err, result){
        if(err){
            response.json(err);
        }
        else
        {
            //palautetaan objekti
            response.json(result);
        }
    })
});

router.post('/',function(request,response){
    tilitapahtumat.add(request.body, function(err,result){
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
    tilitapahtumat.update(request.params.id, request.body, function(err,result){
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
    tilitapahtumat.delete(request.params.id, function(err,result){
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