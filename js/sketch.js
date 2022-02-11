let serial;
let portName = "/dev/cu.usbmodem143101";
let time;

function setup() {

  // make an instance of the SerialPort object
  serial = new p5.SerialPort();

  // Get a list the ports available
  // You should have a callback defined to see the results. See gotList, below:
  serial.list();

  // Assuming our Arduino is connected,  open the connection to it
  // serial.open(portName, {baudrate: 19200});
  serial.open(portName, { baudRate: 9600 }, onOpen)

  // When you get a list of serial ports that are available
  // serial.on('list', gotList);

  // When you some data from the serial port
  serial.on('data', gotData);

  noCanvas();

  let string = "HelloWorld";
  let int = 12;
  let float = 24.7;
  let data = `<${string},${int},${float}>`;
  
  console.log(data)
  time = new Date();
  serial.write(data);
}

function onOpen() {
  console.log("open connection!")
}

// Got the list of ports
function gotList(thelist) {
  print("List of Serial Ports:");
  // theList is an array of their names
  for (let i = 0; i < thelist.length; i++) {
    // Display in the console
    print(i + " " + thelist[i]);
  }
}

// Called when there is data available from the serial port
function gotData() {
  let currentString = serial.readLine();  // read the incoming data
  trim(currentString);                    // trim off trailing whitespace
  if (!currentString) return;             // if the incoming string is empty, do no more
  console.log(currentString);
  console.log(`send and receive took ${new Date() - time}ms`);
}