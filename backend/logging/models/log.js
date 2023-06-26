const mongoose = require('mongoose')
const Schema = mongoose.Schema

const logSchema = new Schema({
    temperature: {
        type: String,
        required: true
    },
    date_time: {
        type: String,
        required: true
    }
})

module.exports = mongoose.model('Log', logSchema)