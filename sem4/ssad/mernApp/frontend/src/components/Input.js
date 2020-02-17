import React from 'react';

const Input = (props)=>{
    return(
        <>
            <label htmlFor={props.name}>{props.labelName}>Email address</label>
            <input type="text" 
                   className="form-control" 
                   placeholder={props.placeholder} 
                   name={props.name} 
                   onChange={props.handleChange} 
                   value={props.value}></input>
        </>
    )
}

export default Input;