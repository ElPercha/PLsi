// Copyright (c) 2019 Lucas Prieto
// Licensed under the MIT License. See LICENSE file in the project root for full license information.

#ifndef TSKWIFI_H
#define TSKWIFI_H

//--------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------

uint16_t configFirmwareEnabled = 0;
uint16_t configFirmwareSequence = 0;
uint16_t configFirmwareMemory = 0;

uint32_t previousFreeMemory = 0;

//--------------------------------------------------------------------------------
// Web Server Object 
//--------------------------------------------------------------------------------

WebServer server(80); 

//--------------------------------------------------------------------------------
// Modbus TCP 
//--------------------------------------------------------------------------------

ModbusIP modbusTCP;
IPAddress remote;  // Address of Modbus Slave device

//--------------------------------------------------------------------------------
// Server Index Page and Style
//--------------------------------------------------------------------------------

const char* serverIndex =
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update'>"
        "<input type='submit' value='Update'>"
    "</form>"
"<div id='prg'>progress: 0%</div>"
"<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')" 
"},"
"error: function (a, b, c) {"
"}"
"});"
"});"
"</script>";

#endif