const mongoose = require('mongoose')
const Schema = mongoose.Schema

const logSchema = new Schema({
    temperature: {
        type: Number,
        required: true
    },
    date_time: {
        type: Date,
        required: true
    }
})

module.exports = mongoose.model('Log', logSchema)