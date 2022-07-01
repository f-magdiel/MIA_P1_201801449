import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SistemausuarioComponent } from './sistemausuario.component';

describe('SistemausuarioComponent', () => {
  let component: SistemausuarioComponent;
  let fixture: ComponentFixture<SistemausuarioComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ SistemausuarioComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(SistemausuarioComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
