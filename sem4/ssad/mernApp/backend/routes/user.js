const express = require('express');
const userRouter = express.Router();
const User = require("../model/User");

// CRUD, Create Read Update Delete ( Following that model)

//Read
userRouter.get('/',(res,req)=>{
    User.find({},(err,response)=>{
        if(err)
            res.status(500).json({message:{
                msgBody: "Unable to connect to get users",
                msgError: true
            }});
        else
            res.status(200).json(response);
    });
});

//Create
userRouter.post('/',(req,res)=>{
    const user = new User(req.body);
    user.save((err,document)=>{
        if(err)
            res.status(500).json({message:{
                msgBody: "Unable to Add User",
                msgError: true
            }});
        else
            res.status(200).json({message:{
                msgBody: "Sucessfully Added User",
                msgError: false
            }});
    });
});

// Delete
userRouter.delete('/:id',(req,res)=>{
    User.findByIdAndDelete(req.params.id,err=>{
        if(err)
            res.status(500).json({message:{
                msgBody: "Unable to Delete User",
                msgError: true
            }});
        else
            res.status(200).json({message:{
                msgBody: "Sucessfully Deleted User",
                msgError: false
            }});
    });
});

// Update
userRouter.put('/:id',(req,res)=>{
    User.findOneAndUpdate(req.params.id,req.body,{runValidators: true},(err,response)=>{
        if(err)
            res.status(500).json({message:{
                msgBody: "Unable to Update User",
                msgError: true
            }});
        else
            res.status(200).json({message:{
                msgBody: "Sucessfully Updated User",
                msgError: false
            }});
    });
});

module.exports = userRouter;