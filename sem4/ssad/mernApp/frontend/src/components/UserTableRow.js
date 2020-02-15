import React from 'react';

const UserTableRow = (props) =>{
    const {firstName,lastName,job,_id} = props.user;
    return(
        <tr>
            <th scope="row">{_id}</th>
            <td>{firstName}</td>
            <td>{lastName}</td>
            <td>{job}</td>
            <td>
                <div className="btn-group" role="group" aria-label="Basic example">
                    <button type="button" onClick={props.showEditForm.bind(this,props.user)} className="btn btn-secondary">Edit</button>
                    <button type="button" onClick={props.deleteHandler.bind(this,props,_id)} className="btn btn-danger">Delete</button>
                </div>
            </td>
        </tr>
    )
}