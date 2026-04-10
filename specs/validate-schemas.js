const fs = require('fs');
const path = require('path');
const Ajv = require('ajv');

const ajv = new Ajv({ strict: false });
const dir = path.join(__dirname, 'schemas');
const files = fs.readdirSync(dir).filter(f => f.endsWith('.json'));
let failed = false;

console.log(`Found ${files.length} schema(s) in ${dir}`);
files.forEach(file => {
  const fp = path.join(dir, file);
  try {
    const schema = JSON.parse(fs.readFileSync(fp, 'utf8'));
    ajv.compile(schema);
    console.log(`OK: ${file}`);
  } catch (err) {
    console.error(`ERROR compiling ${file}: ${err && err.message ? err.message : err}`);
    failed = true;
  }
});

if (failed) {
  console.error('One or more schemas failed to compile.');
  process.exit(1);
} else {
  console.log('All schemas compiled successfully.');
  process.exit(0);
}
