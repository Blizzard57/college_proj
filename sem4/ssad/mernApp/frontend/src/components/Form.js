import React from 'react';
import Input from './Input'

const Form = (props)=>{
    retrurn(
        <form onSubmit={props.handler}>
            <h3>{props.isEditForm ? "Editing User" : "Add Employee"}</h3>
            <div className="form-group">
                <Input name="firstName"
                       placeholder="Enter First Name"
                       labelName="First Name: "
                       handleChange={props.handleChange}
                       value={props.user.firstName} />
                <Input name="lastName"
                       placeholder="Enter Last Name"
                       labelName="Last Name: "
                       handleChange={props.handleChange}
                       value={props.user.lastName} />
                <Input name="job"
                       placeholder="Enter Job"
                       labelName="Job: "
                       handleChange={props.handleChange}
                       value={props.user.job} />
            </div>
            <button type="submit" className="btn btn-primary">Submit</button>
        </form>
    )
}

export default Form;