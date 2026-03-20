const {PrismaClient} = require('@prisma/client');
const prisma = new PrismaClient();

async function main() {
  const products = [];

  for (let i = 1; i<=20; i++){
    products.push({
      name: `produk contoh ${i}`,
      category: i % 2 === 0 ? 'elektronik' : 'pakaian',
      price: i * 10000.0,
      stock: i * 5,
      description: `ini deskripsi dummy untuk produk nomor ${i}`,
    });
  }

  console.log('seeding...')

  await prisma.product.createMany({
    data: products,
  });

  console.log('20 data dumy berhasil dibuat');

}

main()
  .catch((e) => {
    console.error(e);
    process.exit(1);
  })
  .finally(async() => {
    await prisma.$disconnect();
  });
