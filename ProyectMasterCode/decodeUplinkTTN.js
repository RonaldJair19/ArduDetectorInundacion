function decodeUplink(input) {
    var payload = {};
    var warn = [];
    var err = [];
    if(input.fPort == 2){
      warn.push("Utilizar el puerto 1");
    } else if(input.fPort == 3){
      err.push("No utilizar el puerto 3");
    } else {
      payload.port = input.fPort;
      payload.color = input.bytes[0];
      payload.levelColor = input.bytes[1];
      payload.time = (input.bytes[2] << 24)+(input.bytes[3] << 16)+(input.bytes[4] << 8)+(input.bytes[5])
      payload.distance = ((input.bytes[6] << 8) + input.bytes[7])/10;
      payload.velocity = (payload.distance/payload.time).toFixed(4);
    }
    return {
      data: payload,
      warnings: warn,
      errors: err
    };
  }