const { PrismaClient } = require('../generated/prisma');
const bcrypt = require('bcrypt');

const prisma = new PrismaClient();

async function main() {
  const hashedPassword = await bcrypt.hash('adminsukasawit@123', 10);

  const admin = await prisma.user.upsert({
    where: { email: 'sawitwowo@gmail.com' },
    update: {},
    create: {
      name: 'Admin',
      email: 'sawitwowo@gmail.com',
      password: hashedPassword,
      role: 'admin',
      dateOfBirth: new Date('2000-01-10'),
    },
  });

  console.log('Seeded admin:', admin.email);
}

main()
  .catch((e) => {
    console.error(e);
    process.exit(1);
  })
  .finally(async () => {
    await prisma.$disconnect();
  });
