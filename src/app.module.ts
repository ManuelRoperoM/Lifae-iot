import { Module } from '@nestjs/common';
import { RandomDataModule } from './random-data/random-data.module';

@Module({
  imports: [RandomDataModule],
})
export class AppModule {}
