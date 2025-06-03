const express = require('express');
const router = express.Router();
const kortti=require('../models/kortti_model');

router.get('/',function(request,response){
    kortti.getAll(function(err, result){
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
    kortti.getById(request.params.id,function(err, result){
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

router.get('/:id/2',function(request, response){
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


router.post('/',function(request,response){
    kortti.add(request.body, function(err,result){
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
    kortti.update(request.params.id, request.body, function(err,result){
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

router.delete('/:id',function(request,response){
    kortti.delete(request.params.id, function(err,result){
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