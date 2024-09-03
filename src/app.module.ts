import { Module } from '@nestjs/common';
import { MeteringsModule } from './meterings/meterings.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Meterings } from './meterings/meterings.entity';

@Module({
  imports: [
    TypeOrmModule.forRoot({
      type: 'postgres',
      host: 'localhost',
      port: 5432,
      password: 'postgres',
      username: 'postgres',
      entities: [Meterings],
      database: 'lifaeIOT',
      synchronize: true,
      logging: true,
    }),
    MeteringsModule,
  ],
})
export class AppModule {}
