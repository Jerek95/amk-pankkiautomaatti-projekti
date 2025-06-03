const db=require('../database.js');

const login={
    
    getById(id, callback){
        return db.query('SELECT * FROM kortti WHERE kortinnumero=?',[id],callback);
    }
}

module.exports=login;